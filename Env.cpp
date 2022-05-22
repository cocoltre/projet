#include <iostream>
#include "Env.hpp"
#include "Application.hpp"
#include <fstream>
#include <Random/Random.hpp>
#include <vector>
#include "Flower.hpp"
#include "Utility/Utility.hpp"

// CONSTRUCTOR AND DESTRUCTORS
Env::Env () {                                   // constructor by default
    loadWorldFromFile();
}

void Env::delete_flowers () {                   // delete all the flowers' collection
    if (Flowers.size() != 0) {
        for (size_t i(0); i < Flowers.size(); ++i) {
            delete Flowers[i];
            Flowers[i] = nullptr;
        }
        Flowers.erase(std::remove(Flowers.begin(), Flowers.end(), nullptr), Flowers.end());
    }
}

void Env::delete_hives () {                     // delete all the Hives' collection
    if (Hives.size() != 0) {
        for (size_t i(0); i < Hives.size(); ++i) {
            delete Hives[i];
            Hives[i] = nullptr;
        }
        Hives.erase(std::remove(Hives.begin(), Hives.end(), nullptr), Hives.end());
    }
}


// RELATIVE TO EVOLUTION
void Env::update(sf::Time dt) {                 // update the Env's evolution
    flowergenerator.update(dt);
    if (Flowers.size() != 0) {
        for (size_t i(0); i < Flowers.size(); ++i) {
            Flowers[i]->update(dt);
            if (Flowers[i]->get_pollen() == 0.00) {
                delete Flowers[i];
                Flowers[i] = nullptr;
            }
        }
        Flowers.erase(std::remove(Flowers.begin(), Flowers.end(), nullptr), Flowers.end());
    }

    for (size_t i(0); i < Hives.size(); ++i) {
       Hives[i]->update(dt);
    }
}

void Env::drawOn(sf::RenderTarget& target) const {          // draw the Env
    world.drawOn(target);
    if (Flowers.size() != 0) {
        for (size_t i(0); i < Flowers.size(); ++i) {
            Flowers[i]->drawOn(target);
        }
    }
    if (Hives.size() != 0) {
        for (size_t i(0); i < Hives.size(); ++i) {
            Hives[i]->drawOn(target);
        }
    }
}

void Env::drawFlowerZone(sf::RenderTarget& target, Vec2d const& position) const {                     // draw a zone around a specific position, whose color determines
                                                                                                // whether the position can host a new Flower or not
    double size = getValueConfig()["simulation"]["env"]["initial"]["flower"]["size"]["manual"].toDouble();
    double thickness (3.0);
    sf::Color color;
    Collider col (position, size);
    if (world.isGrowable(world.coord(position)) and (getCollidingHive(col) == nullptr)) {
        color = sf::Color::Green;
    }
    else {
        color = sf::Color::Red;
    }
    auto shape = buildAnnulus(position, size, color, thickness);
    target.draw(shape);
}

void Env::drawHiveableZone(sf::RenderTarget& target, Vec2d const& position) {       // draw a zone around a specific position, whose color
                                                                                    // determines whether the position can host a new Hive or not
    double thickness (5.0);
    sf::Color color;

    double size (getAppConfig().hive_manual_size);
    double factor (getAppConfig().hiveable_factor);
    Collider col (position, size*factor);

    if ((getCollidingHive(col) != nullptr) or (getCollidingFlower(col) != nullptr)) {   // if there is a collision with a Hive or a Flower
        color = sf::Color::Blue;
    }
    else if (world.isHiveable(position, size*factor) == false) {                        // if there is no collision but the position is not made of grass
        color = sf::Color::Red;
    }
    else {                                                                              // if there is no collision and the position is made of grass
        color = sf::Color::Green;
    }

    // drawing of the rectangle according to the position of the cursor
    Vec2d LeftTop ((position.x()-size*factor), (position.y()-size*factor));
    Vec2d TopBottom ((position.x()+size*factor), (position.y()+size*factor));
    Vec2d newLeftTop (world.coord(LeftTop));                                    // coordinates in the world made of cells (without taking into account their size)
    Vec2d newTopBottom (world.coord(TopBottom));
    double world_size (world.getSize());             // width of the world if we take into account the size of the cells

    if ((position.x() > 0.00) and (position.y() > 0.00) and (position.x() < world_size) and (position.y() < world_size)) { // if the cursor is inside the world
        // left border
        if ((newLeftTop.x() < 0.00)) {
            if ((newLeftTop.y() > 0.00)) {
                if ((newTopBottom.y() < world.get_nbcells_())) {      // inner left side
                    sf::RectangleShape shape2(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x(), TopBottom.y()}, color, thickness)); // left side
                    sf::RectangleShape shape21(buildRectangle({ LeftTop.x()+ world_size, LeftTop.y() }, { world_size, TopBottom.y() }, color, thickness));  // right side
                    target.draw(shape2);
                    target.draw(shape21);
                }
                else {                                                // bottom left corner
                    sf::RectangleShape shape2(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x(), world_size}, color, thickness));   // bottom left side
                    sf::RectangleShape shape21(buildRectangle({ LeftTop.x()+ world_size, LeftTop.y() }, { world_size, world_size }, color, thickness)); // bottom right side
                    sf::RectangleShape shape22(buildRectangle({ LeftTop.x()+ world_size, 0.00 }, { world_size, TopBottom.y() - world_size}, color, thickness)); // top right side
                    sf::RectangleShape shape23(buildRectangle({0.00, 0.00 }, { TopBottom.x(), TopBottom.y() - world_size}, color, thickness));  // top left side
                    target.draw(shape2);
                    target.draw(shape21);
                    target.draw(shape22);
                    target.draw(shape23);
                }
            }
            else {      // top left corner
                sf::RectangleShape shape2(buildRectangle({ 0.00, 0.00 }, { TopBottom.x(), TopBottom.y() }, color, thickness));   // top left side
                sf::RectangleShape shape21(buildRectangle({ 0.00, LeftTop.y() + world_size}, { TopBottom.x(), world_size }, color, thickness)); // bottom left side
                sf::RectangleShape shape22(buildRectangle({ LeftTop.x()+ world_size, 0.00 }, { world_size, TopBottom.y() }, color, thickness)); // top right side
                sf::RectangleShape shape23(buildRectangle({ LeftTop.x() + world_size, LeftTop.y() + world_size }, { world_size, world_size }, color, thickness));  // bottom right side
                target.draw(shape2);
                target.draw(shape21);
                target.draw(shape22);
                target.draw(shape23);
            }
        }

        // right border
        else if ((newTopBottom.x() > world.get_nbcells_())) {
            if (newLeftTop.y() > 0.00) {
                if (newTopBottom.y() < world.get_nbcells_()) {      // inner right side
                    sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), LeftTop.y() }, { world_size, TopBottom.y() }, color, thickness)); // right side
                    sf::RectangleShape shape31(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x() - world_size, TopBottom.y() }, color, thickness)); // left side
                    target.draw(shape3);
                    target.draw(shape31);
                }
                else {              // bottom right corner
                    sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), LeftTop.y() }, { world_size, world_size }, color, thickness));   // bottom right side
                    sf::RectangleShape shape31(buildRectangle({ LeftTop.x(), 0.00 }, { world_size, TopBottom.y() - world_size }, color, thickness)); // top right side
                    sf::RectangleShape shape32(buildRectangle({ 0.00, 0.00 }, { TopBottom.x() - world_size, TopBottom.y() - world_size }, color, thickness)); // top left side
                    sf::RectangleShape shape33(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x() - world_size, world_size }, color, thickness));  // bottom left side
                    target.draw(shape3);
                    target.draw(shape31);
                    target.draw(shape32);
                    target.draw(shape33);
                }
            }
            else {      // top right corner
                sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), 0.00 }, { world_size, TopBottom.y() }, color, thickness));   // top right side
                sf::RectangleShape shape31(buildRectangle({ LeftTop.x(), LeftTop.y() + world_size}, { world_size, world_size }, color, thickness)); // bottom right side
                sf::RectangleShape shape32(buildRectangle({ 0.00, 0.00 }, { TopBottom.x() - world_size, TopBottom.y() }, color, thickness)); // top left side
                sf::RectangleShape shape33(buildRectangle({ 0.00, LeftTop.y() + world_size }, { TopBottom.x() - world_size, world_size }, color, thickness));  // bottom left side
                target.draw(shape3);
                target.draw(shape31);
                target.draw(shape32);
                target.draw(shape33);
            }
        }

        // inner surface, inner and upper sides
        else if (LeftTop.y() > 0.00) {
            if ((newTopBottom.y() > world.get_nbcells_())) {        // lower side
                sf::RectangleShape shape5(buildRectangle({LeftTop.x(), 0.00}, { TopBottom.x(), TopBottom.y()- world_size}, color, thickness)); // top side
                sf::RectangleShape shape51(buildRectangle({LeftTop.x(), LeftTop.y() }, { TopBottom.x(), (double)world_size}, color, thickness)); // bottom side
                target.draw(shape5);
                target.draw(shape51);
            }
            else {      // inside the area
                sf::RectangleShape shape(buildRectangle({LeftTop.x(), LeftTop.y() }, { TopBottom.x(), TopBottom.y() }, color, thickness));
                target.draw(shape);
            }
        }

        else {          // upper side
            sf::RectangleShape shape4(buildRectangle({LeftTop.x(), 0.00}, { TopBottom.x(), TopBottom.y()}, color, thickness));      // top side
            sf::RectangleShape shape41(buildRectangle({LeftTop.x(), LeftTop.y() + world_size}, { TopBottom.x(), (double)world_size}, color, thickness));    // bottom side
            target.draw(shape4);
            target.draw(shape41);
        }
    }
}

void Env::reset() {                     // reset the Env
    delete_flowers();
    delete_hives();
    flowergenerator.reset();
    world.reset();
}

void Env::resetControls() {}            // reset all controls


// RELATIVE TO FILE MANAGEMENT
void Env::loadWorldFromFile() {         // lord a World from a file
    delete_flowers();
    delete_hives();
    flowergenerator.reset();
    try {
        world.loadFromFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        reset();
    }
}

void Env::saveWorldToFile() {           // save the World to a specific file
    try {
        world.saveToFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
    }
}


// GETTERS
float Env::getSize () const {                   // get the Env's World's size
    return world.getSize();
}

std::vector <Flower*> Env::get_flowers() const {      // get the Env's Flowers' collection
    return Flowers;
}

double Env::find_humidity (Vec2d p) const {           // find the humidity of a specific position
    p = world.coord(p);
    return world.get_humid_cells()[world.index_cell(p.x(), p.y())];
}


// TESTS
bool Env::IsFlyable(const Vec2d& p) const {           // check if a specific position is made of rocks meaning that a Bee cannot fly there
    return world.IsFlyable(p);
}

Hive* Env::getCollidingHive(const Collider& body) const {           // find a Hive in the Env that is colliding with a specific Collider
    auto const& size (getAppConfig().hive_manual_size);
    auto const& factor (getAppConfig().hiveable_factor);
    for (size_t i(0); i < Hives.size(); ++i) {
        if (body | Collider(Hives[i]->getPosition(), size*factor)) {
            return Hives[i];
        }
    }
    return nullptr;
}

Flower* Env::getCollidingFlower(const Collider& body) const {       // find a Flower in the Env that is colliding with a specific Collider
    for (size_t i(0); i < Flowers.size(); ++i) {
        if (body | Collider(Flowers[i]->getPosition(), Flowers[i]->getRadius())) {
            return Flowers[i];
        }
    }
    return nullptr;
}


// CHANGE THE ENV
bool Env::addFlowerAt (const Vec2d& p) {                // add a Flower at a specific position if it is possible
    double size = getValueConfig()["simulation"]["env"]["initial"]["flower"]["size"]["manual"].toDouble();
    Collider col (p, size);
    if ((world.isGrowable(world.coord(p))) and (int(Flowers.size()) < getValueConfig()["simulation"]["env"]["max flowers"].toInt()) and (getCollidingHive(col) == nullptr)) {
        Flowers.push_back(new Flower (p, getAppConfig().flower_manual_size, uniform(getAppConfig().flower_nectar_min, getAppConfig().flower_nectar_max)));
        return true;
    }
    else {
        return false;
    }
}

bool Env::addHiveAt(const Vec2d& position) {            // add a Hive at a specific position if it is possible
    double radius (uniform(getAppConfig().hive_min_size, getAppConfig().hive_max_size));
    auto const& size (getAppConfig().hive_manual_size);
    auto const& factor (getAppConfig().hiveable_factor);
    Hive big_hive (position, size*factor);
    if ((getCollidingHive(big_hive) != nullptr) or (getCollidingFlower(big_hive) != nullptr) or (world.isHiveable(position, size*factor) == false)) {    // if the conditions for creating a new Hive there are not reunited
        return false;
    }
    else {        
        Hives.push_back(new Hive(position, radius));
        return true;
    }
}
