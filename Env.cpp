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
}

void Env::reset() { // permet de regénèrer l'environnement
    delete_flowers();
    flowergenerator.reset();
    this->world.reset();
}

Env::Env () { // constructeur par défaut
    loadWorldFromFile();
}

void Env::loadWorldFromFile() { // charge l'environnement depuis un fichier
    delete_flowers();
    try {
        this->world.loadFromFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        reset();
    }
}

float Env::getSize () const { // renvoie la taille du terrain
    return this->world.getSize();
}

void Env::resetControls() {} // remet à zéro les contrôles

bool Env::addFlowerAt (const Vec2d& p) {        // ajoute une fleur si la cellule est d'herbe et renvoie alors vrai
    if (world.isGrowable(world.coord(p)) and (int(Flowers.size()) < getValueConfig()["simulation"]["env"]["max flowers"].toInt())) {
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
    if (world.isGrowable(world.coord(position))) {
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




