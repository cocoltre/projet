#include <iostream>
#include "World.hpp"
#include "Flower.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "FlowerGenerator.hpp"
#include "Hive.hpp"
#pragma once

class Env : public Drawable, public Updatable {
private :
    World world;
    std::vector <Flower*> Flowers;
    FlowerGenerator flowergenerator;
    std::vector <Hive*> Hives;

public :
    Env ();     // constructeur par défaut
    ~Env () {   // destructeur
        delete_flowers();
        delete_hives();
    }
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& target) const ;
    void reset();
    void loadWorldFromFile();
    void saveWorldToFile();
    float getSize () const;
    void resetControls();

    bool addFlowerAt (const Vec2d& p);
    void delete_flowers ();
    void drawFlowerZone(sf::RenderTarget& target, Vec2d const& position);
    double find_humidity (Vec2d p);

    bool addHiveAt(const Vec2d& position);
    Hive* getCollidingHive(const Collider& body) const;
    Flower* getCollidingFlower(const Collider& body) const;
    void delete_hives ();
    bool IsThereAHive (const Vec2d& p, double radius);

    void drawHiveableZone(sf::RenderTarget& target, Vec2d const& position);
    bool IsThereAFlower (const Vec2d& p, double radius);

    bool IsFlyable (const Vec2d& p);

    std::vector <Flower*> get_flowers();

};
