#include <iostream>
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

#pragma once

class FlowerGenerator {
private :
    sf::Time counter;

public :
    FlowerGenerator () {counter = sf::Time::Zero;}; // constructeur par défaut
    void update(sf::Time dt);
    void reset();
};
