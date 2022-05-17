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
    Hive& Home;
    Vec2d speed;
    double energy;
    Vec2d memory;
    bool memory_value;
    std::string mode;
    Vec2d target;
    sf::Time avoidanceClock_;

public:
    Bee(Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states);
    ~Bee () {};

    void move(sf::Time dt);
    void targetMove(sf::Time dt);
    void randomMove(sf:: Time dt);
    bool Isdead ();
    virtual j::Value getConfig() const& = 0 ;
    virtual void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double get_energy() const;

    virtual void onState (state const& s, sf::Time dt) = 0;
    virtual void onEnterState(state const& s)  = 0;
    void change_mode(std::string newmode);
    void change_target(Vec2d const& newtarget);
    void change_memory(Vec2d const& newmemory);
    void change_value_memory();
    bool get_value_memory() const;

    Vec2d home_position ();
    double home_radius();

    void gain_energy(double qte);



};
