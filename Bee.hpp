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
    Vec2d* memory;
    std::string mode;
    Vec2d target;

public:
    Bee(Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states, Vec2d* memory2);
    ~Bee () {};

    void move(sf::Time dt);
    void targetMove(sf::Time dt);
    void randomMove(sf:: Time dt);
    bool Isdead ();
    virtual j::Value getConfig() const& = 0 ;
    void drawOn(sf::RenderTarget& target) const;
    void update(sf::Time dt);
    double get_energy();

    virtual void onState (state const& s, sf::Time dt);
    virtual void onEnterState(state const& s)  ;
    void change_mode(std::string newmode);
    void change_target(Vec2d const& newtarget);
    void change_memory(Vec2d const* newmemory);
    Vec2d* get_memory();

    Vec2d home_position ();
    double home_radius();

    void gain_energy(double qte);



};
