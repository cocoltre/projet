#include <iostream>
#include "Hive.hpp"
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once


class Bee: public Collider, public Drawable, public Updatable {
private:
    Hive& Home;
    Vec2d speed;
    double energy;
    sf::Texture const& texture;

public:
    Bee(Hive& Home, const Vec2d& position, const double& arg_rad, const double& energy, const double& ScalSpeed);
    ~Bee () {};

    void move(sf:: Time dt);
    bool Isdead ();
    virtual j::Value const& getConfig() ;
    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double get_energy();

};
