#include <iostream>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once

class Flower : public Collider, public Drawable, public Updatable {
private :
    double pollen;
    int indice;

public :
    Flower (Vec2d position, double arg_diam, double arg_pollen); // constructeur
    double takePollen (double amount);
    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double get_pollen ();
};
