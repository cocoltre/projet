#include <iostream>
#include "World.hpp"
#include "Flower.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "FlowerGenerator.hpp"
#pragma once

class Env : public Drawable, public Updatable {
private :
    World world;
    std::vector <Flower*> Flowers;
    FlowerGenerator flowergenerator;

public :
    Env ();     // constructeur par défaut
    ~Env () {   // destructeur
        delete_flowers();
    }
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& target) const ;
    void reset();
    void loadWorldFromFile();
    float getSize () const;
    void resetControls();

    bool addFlowerAt (const Vec2d& p);
    void delete_flowers ();
    void drawFlowerZone(sf::RenderTarget& target, Vec2d const& position);
    double find_humidity (Vec2d p);
};
