#include <iostream>
#include "Hive.hpp"
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once


class Bee: public Collider, public Drawable, public Updatable{
private:
    Hive& Home;
    Vec2d speed;
    double energy;

public:
    Bee(const Vec2d& position, const double& arg_diam, Hive& Home, const double& energy, const double& ScalSpeed);

    void move(sf:: Time dt);
    bool life;
    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double alpha(double Vec2d::angle(speed));
};

