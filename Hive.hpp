#include <iostream>
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once

class Bee; // prédéclaration

class Hive : public Collider, public Drawable, public Updatable {
private :
    std::vector<Bee*> Bees;
    double pollen;

public :
    Hive (Vec2d position, double arg_radius); // constructeur
    Hive(const Hive& temp_obj) = delete;            // constructeur de copie supprimé
    Hive& operator=(const Hive& temp_obj) = delete;   // opérateur = supprimé
    ~Hive () {              // destructeur
        delete_bees();
    };
    void addBee();
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& targetWindow) const;
    void dropPollen(double qte);
    double takeNectar(double qte);
    void delete_bees ();

};
