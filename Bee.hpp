#include <iostream>
#include "Hive.hpp"
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CFSM.hpp"
#pragma once


class Bee: public Collider, public Drawable, public Updatable, public CFSM {
private:
    const Hive& Home;
    Vec2d speed;
    double energy;
    Vec2d* memory;
    std::string mode;
    Vec2d target;

public:
    Bee(const Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states, Vec2d* memory2);
    ~Bee () {};

    void move(sf::Time dt);
    void targetMove(sf::Time dt);
    void randomMove(sf:: Time dt);
    bool Isdead ();
    virtual j::Value getConfig() const& = 0 ;
    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double get_energy();

};
