#include <iostream>
#include "Bee.hpp"

#pragma once

class WorkerBee : public Bee {
private :
    static state const IN_HIVE  ;
    static state const TO_FLOWER  ;
    static state const NECTAR_COLLECT  ;
    static state const BACK_TO_HIVE ;

    double nectar;

public :
    WorkerBee (Hive& Home, const Vec2d& position);
    ~WorkerBee() {}
    virtual j::Value getConfig() const&;
    virtual void onState (state const& s, sf::Time dt);
    virtual void onEnterState(state const& s)  ;
    virtual void drawOn(sf::RenderTarget& target) const;
    virtual void interact(Bee* other) ;
    virtual void interactWith(ScoutBee* scouting) ;
    virtual void interactWith(WorkerBee* working) ;

    void takePollen(double qte, int i) ;
    static state get_in_hive();
};
