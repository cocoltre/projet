#include <iostream>
#include "Env.hpp"
#include "Application.hpp"
#include <fstream>

void Env::update(sf::Time dt) { // fait évoluer l'environnement sur une période de temps dt
    this->world.updateCache();
}

void Env::drawOn(sf::RenderTarget& target) { // permet de dessiner le contenu de l'environnement
    this->world.drawOn(target);
}

void Env::reset() { // permet de regénèrer l'environnement
    this->world.reset();
}

Env::Env () { // constructeur par défaut
    try {
        this->world.loadFromFile();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what();
        reset();
    }
}

void Env::loadWorldFromFile() { // charge l'environnement depuis un fichier
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
