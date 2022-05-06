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

    for (size_t i(0); i < Hives.size(); ++i) {
       Hives[i]->update(dt);
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

bool Env::addFlowerAt (const Vec2d& p) {        // ajoute une fleur si possible et renvoie alors vrai
    double size = getValueConfig()["simulation"]["env"]["initial"]["flower"]["size"]["manual"].toDouble();
    if ((world.isGrowable(world.coord(p))) and (int(Flowers.size()) < getValueConfig()["simulation"]["env"]["max flowers"].toInt()) and (IsThereAHive(p,size) == false)) {
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
                                                                                                // la fleur peut être plantée ou non
    double size = getValueConfig()["simulation"]["env"]["initial"]["flower"]["size"]["manual"].toDouble();
    double thickness (3.0);
    sf::Color color;
    if (world.isGrowable(world.coord(position)) and (IsThereAHive(position, size) == false)) {
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
    if ((getCollidingHive(big_hive) != nullptr) or (getCollidingFlower(big_hive) != nullptr) or (world.isHiveable(position, radius) == false)) {
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

bool Env::IsThereAHive (const Vec2d& p, double radius) {               // renvoie vrai si une ruche occupe la position p
    Vec2d a (world.coord({p.x() - radius, p.y() - radius}));
    Vec2d b (world.coord({p.x() + radius, p.y() + radius}));

    for (size_t i(0); i < Hives.size(); ++i) {
        for (int j(a.x()); j < b.x(); ++j) {
            for (int k(a.y()); k < b.y(); ++k) {
                if (world.coord(Hives[i]->getPosition()) == Vec2d(j,k)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Env::IsThereAFlower (const Vec2d& p, double radius) {               // renvoie vrai si une fleur occupe la position p
    Vec2d a (world.coord({p.x() - radius, p.y() - radius}));
    Vec2d b (world.coord({p.x() + radius, p.y() + radius}));

    /*for (size_t i(0); i < Flowers.size(); ++i) {
        for (int j(a.x()); j < b.x(); ++j) {
            for (int k(a.y()); k < b.y(); ++k) {
                if (world.coord(Flowers[i]->getPosition()) == Vec2d(j,k)) {
                    return true;
                }
            }
        }
    }*/
            for (int j(a.x()); j < b.x(); ++j) {
                for (int k(a.y()); k < b.y(); ++k) {
                    Collider col({double(j), double(k)}, 1.0);
                    if (getCollidingFlower(col) != nullptr) {
                        return true;
                    }
                }
            }


    return false;
}

void Env::drawHiveableZone(sf::RenderTarget& target, Vec2d const& position) {       // dessine un carré autour du curseur qui selon sa couleur détermine si
                                                                                    // une ruche peut être plantée ou non
    double thickness (5.0);
    sf::Color color;

    double size (getAppConfig().hive_manual_size);
    double factor (getAppConfig().hiveable_factor);

    if ((IsThereAHive(position, size*factor) == true) or (IsThereAFlower(position, size*factor) == true)) {
        color = sf::Color::Blue;
    }
    else if (world.isHiveable(position, size*factor) == false) {
        color = sf::Color::Red;
    }
    else {
        color = sf::Color::Green;
    }

    // dessin du rectangle en fonction de la position du curseur
    Vec2d LeftTop ((position.x()-size*factor), (position.y()-size*factor));
    Vec2d TopBottom ((position.x()+size*factor), (position.y()+size*factor));
    Vec2d newLeftTop (world.coord(LeftTop));                // coordonnées dans le monde faits de cellules (sans prendre en compte leur taille)
    Vec2d newTopBottom (world.coord(TopBottom));
    double world_size (world.get_nbcells_()*world.get_cell_size()); // largeur du monde si on prend en compte la taille des cellules

    if ((newLeftTop.x() < 0.00)) {                          // côté gauche
        if ((newLeftTop.y() > 0.00)) {
            if ((newTopBottom.y() < world.get_nbcells_())) {      // côté gauche intérieur
                sf::RectangleShape shape2(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x(), TopBottom.y()}, color, thickness)); // partie gauche
                sf::RectangleShape shape21(buildRectangle({ LeftTop.x()+ world_size, LeftTop.y() }, { world_size, TopBottom.y() }, color, thickness));  // partie droite
                target.draw(shape2);
                target.draw(shape21);
            }
            else {                                                // coin gauche en bas
                sf::RectangleShape shape2(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x(), world_size}, color, thickness));   // partie gauche du bas
                sf::RectangleShape shape21(buildRectangle({ LeftTop.x()+ world_size, LeftTop.y() }, { world_size, world_size }, color, thickness)); // partie droite du bas
                sf::RectangleShape shape22(buildRectangle({ LeftTop.x()+ world_size, 0.00 }, { world_size, TopBottom.y() - world_size}, color, thickness)); // partie droite du bas
                sf::RectangleShape shape23(buildRectangle({0.00, 0.00 }, { TopBottom.x(), TopBottom.y() - world_size}, color, thickness));  // partie gauche du haut
                target.draw(shape2);
                target.draw(shape21);
                target.draw(shape22);
                target.draw(shape23);
            }
         }
        else {      // coin gauche du haut
            sf::RectangleShape shape2(buildRectangle({ 0.00, 0.00 }, { TopBottom.x(), TopBottom.y() }, color, thickness));   // partie gauche du haut
            sf::RectangleShape shape21(buildRectangle({ 0.00, LeftTop.y() + world_size}, { TopBottom.x(), world_size }, color, thickness)); // partie gauche du bas
            sf::RectangleShape shape22(buildRectangle({ LeftTop.x()+ world_size, 0.00 }, { world_size, TopBottom.y() }, color, thickness)); // partie droite du haut
            sf::RectangleShape shape23(buildRectangle({ LeftTop.x() + world_size, LeftTop.y() + world_size }, { world_size, world_size }, color, thickness));  // partie droite du bas
            target.draw(shape2);
            target.draw(shape21);
            target.draw(shape22);
            target.draw(shape23);
        }
    }
    else if ((newTopBottom.x() > world.get_nbcells_())) {       // côté droit
        if (newLeftTop.y() > 0.00) {
            if (newTopBottom.y() < world.get_nbcells_()) {      // côté droit intérieur
                sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), LeftTop.y() }, { world_size, TopBottom.y() }, color, thickness)); // partie droite
                sf::RectangleShape shape31(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x() - world_size, TopBottom.y() }, color, thickness)); // partie gauche
                target.draw(shape3);
                target.draw(shape31);
            }
            else {              // coin droit du bas
                sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), LeftTop.y() }, { world_size, world_size }, color, thickness));   // partie droite du bas
                sf::RectangleShape shape31(buildRectangle({ LeftTop.x(), 0.00 }, { world_size, TopBottom.y() - world_size }, color, thickness)); // partie droite du haut
                sf::RectangleShape shape32(buildRectangle({ 0.00, 0.00 }, { TopBottom.x() - world_size, TopBottom.y() - world_size }, color, thickness)); // partie gauche du haut
                sf::RectangleShape shape33(buildRectangle({ 0.00, LeftTop.y() }, { TopBottom.x() - world_size, world_size }, color, thickness));  // partie gauche du bas
                target.draw(shape3);
                target.draw(shape31);
                target.draw(shape32);
                target.draw(shape33);
            }
        }
        else {      // coin droit du haut
            sf::RectangleShape shape3(buildRectangle({ LeftTop.x(), 0.00 }, { world_size, TopBottom.y() }, color, thickness));   // partie droite du haut
            sf::RectangleShape shape31(buildRectangle({ LeftTop.x(), LeftTop.y() + world_size}, { world_size, world_size }, color, thickness)); // partie droite du bas
            sf::RectangleShape shape32(buildRectangle({ 0.00, 0.00 }, { TopBottom.x() - world_size, TopBottom.y() }, color, thickness)); // partie gauche du haut
            sf::RectangleShape shape33(buildRectangle({ 0.00, LeftTop.y() + world_size }, { TopBottom.x() - world_size, world_size }, color, thickness));  // partie gauche du bas
            target.draw(shape3);
            target.draw(shape31);
            target.draw(shape32);
            target.draw(shape33);
        }
    }

    // intérieur de la surface, côtés intérieur et supérieur
    else if (LeftTop.y() > 0.00) {
        if ((newTopBottom.y() > world.get_nbcells_())) {        // côté inférieur
            sf::RectangleShape shape5(buildRectangle({LeftTop.x(), 0.00}, { TopBottom.x(), TopBottom.y()- world_size}, color, thickness)); // partie du haut
            sf::RectangleShape shape51(buildRectangle({LeftTop.x(), LeftTop.y() }, { TopBottom.x(), (double)world_size}, color, thickness)); // partie du bas
            target.draw(shape5);
            target.draw(shape51);
        }
        else {      // intérieur de la surface
            sf::RectangleShape shape(buildRectangle({LeftTop.x(), LeftTop.y() }, { TopBottom.x(), TopBottom.y() }, color, thickness));
            target.draw(shape);
        }
    }

    else {          // côté supérieur
        sf::RectangleShape shape4(buildRectangle({LeftTop.x(), 0.00}, { TopBottom.x(), TopBottom.y()}, color, thickness));      // partie du haut
        sf::RectangleShape shape41(buildRectangle({LeftTop.x(), LeftTop.y() + world_size}, { TopBottom.x(), (double)world_size}, color, thickness));    // partie du bas
        target.draw(shape4);
        target.draw(shape41);
    }

}

bool Env::IsFlyable(const Vec2d& p) {       // retourne true si le sol n'est pas de roche
    return world.IsFlyable(p);
}
