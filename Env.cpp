#include <iostream>
#include "Env.hpp"
#include "Application.hpp"
#include <fstream>
#include <Random/Random.hpp>
#include <vector>
#include "Flower.hpp"
#include "Utility/Utility.hpp"

void Env::update(sf::Time dt) { // fait évoluer l'environnement sur une période de temps dt
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
}

void Env::drawOn(sf::RenderTarget& target) const { // permet de dessiner le contenu de l'environnement
    this->world.drawOn(target);
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

void Env::reset() { // permet de regénèrer l'environnement
    delete_flowers();
    delete_hives();
    flowergenerator.reset();
    this->world.reset();
}

Env::Env () { // constructeur par défaut
    loadWorldFromFile();
}

void Env::loadWorldFromFile() { // charge l'environnement depuis un fichier
    delete_flowers();
    delete_hives();
    flowergenerator.reset();
    try {
        this->world.loadFromFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        reset();
    }
}

void Env::saveWorldToFile() {
    try {
        this->world.saveToFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
    }
}

float Env::getSize () const { // renvoie la taille du terrain
    return this->world.getSize();
}

void Env::resetControls() {} // remet à zéro les contrôles

bool Env::addFlowerAt (const Vec2d& p) {        // ajoute une fleur si la cellule est d'herbe et renvoie alors vrai
    if (world.isGrowable(world.coord(p)) and (int(Flowers.size()) < getValueConfig()["simulation"]["env"]["max flowers"].toInt()) and (IsThereAHive(p) == false)) {
        Flowers.push_back(new Flower (p, getAppConfig().flower_manual_size, uniform(getAppConfig().flower_nectar_min, getAppConfig().flower_nectar_max)));
        return true;
    }
    else {
        return false;
    }
}

void Env::delete_flowers () {                   // supprime toutes les fleurs
    if (Flowers.size() != 0) {
        for (size_t i(0); i < Flowers.size(); ++i) {
            delete Flowers[i];
            Flowers[i] = nullptr;
        }
        Flowers.erase(std::remove(Flowers.begin(), Flowers.end(), nullptr), Flowers.end());
    }
}

void Env::drawFlowerZone(sf::RenderTarget& target, Vec2d const& position) {                     // dessine un anneau autour du curseur qui selon sa couleur détermine si
    double size = getValueConfig()["simulation"]["env"]["initial"]["flower"]["size"]["manual"].toDouble();
    double thickness (3.0);
    sf::Color color;
    if (world.isGrowable(world.coord(position)) and (IsThereAHive(position) == false)) {
        color = sf::Color::Green;
    }
    else {
        color = sf::Color::Red;
    }
    auto shape = buildAnnulus(position, size, color, thickness);
    target.draw(shape);
}

double Env::find_humidity (Vec2d p) {           // retourne le taux d'humidité d'une cellule
    p = world.coord(p);
    return world.get_humid_cells()[p.x() + p.y() * world.get_nbcells_()];
}

bool Env::addHiveAt(const Vec2d& position) {        // ajoute une ruche à l'ensemble de ruches
    double radius (uniform(getAppConfig().hive_min_size, getAppConfig().hive_max_size));
    Hive big_hive (position, radius);
    if ((getCollidingHive(big_hive) != nullptr) or (getCollidingFlower(big_hive) != nullptr)) {
        return false;
    }
    else {
        Hives.push_back(new Hive(position, radius));
        return true;
    }
}

Hive* Env::getCollidingHive(const Collider& body) {         // retourne un pointeur sur une ruche de l'environnement en collision avec le body ou nullptr dans le cas contraire
    auto const& size (getAppConfig().hive_manual_size);
    auto const& factor (getAppConfig().hiveable_factor);
    for (size_t i(0); i < Hives.size(); ++i) {
        if (body | Collider(Hives[i]->getPosition(), size*factor)) {
            return Hives[i];
        }
    }
    return nullptr;
}

Flower* Env::getCollidingFlower(const Collider& body) {    // retourne une fleur de l'environnement en collision avec le body ou nullptr dans le cas contraire
    for (size_t i(0); i < Flowers.size(); ++i) {
        if (body | Collider(Flowers[i]->getPosition(), Flowers[i]->getRadius())) {
            return Flowers[i];
        }
    }
    return nullptr;
}

void Env::delete_hives () {         // supprime toutes les ruches
    if (Hives.size() != 0) {
        for (size_t i(0); i < Hives.size(); ++i) {
            delete Hives[i];
            Hives[i] = nullptr;
        }
        Hives.erase(std::remove(Hives.begin(), Hives.end(), nullptr), Hives.end());
    }
}

bool Env::IsThereAHive (const Vec2d& p) {               // renvoie vrai si une ruche occupe la position p
    for (size_t i(0); i < Hives.size(); ++i) {
        if (Hives[i]->getPosition() == p) {
            return true;
        }
    }
    return false;
}

bool Env::IsThereAFlower (const Vec2d& p) {               // renvoie vrai si une ruche occupe la position p
    for (size_t i(0); i < Flowers.size(); ++i) {
        if (Flowers[i]->getPosition() == p) {
            return true;
        }
    }
    return false;
}

void Env::drawHiveableZone(sf::RenderTarget& target, Vec2d const& position) {
    double thickness (5.0);
    sf::Color color;
    double left (0.0);
    double top (0.0);
    double right (0.0);
    double bottom (0.0);

    if ((IsThereAHive(position) == true) or (IsThereAFlower(position) == true)) {
        color = sf::Color::Blue;
    }
    else if (world.get_cells_()[world.coord(position).x() + world.coord(position).y()*world.get_nbcells_()] == Kind::Grass) {
        color = sf::Color::Green;
    }
    else {
        color = sf::Color::Red;
    }

    sf::RectangleShape shape(buildRectangle({ left, top }, { right, bottom }, color, thickness));
    target.draw(shape);
}
