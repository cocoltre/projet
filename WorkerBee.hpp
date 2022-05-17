#include <iostream>
#include "Bee.hpp"

#pragma once

class WorkerBee : public Bee {
private :
    static state const IN_HIVE;
    static state const TO_FLOWER;
    static state const COLLECT_POLLEN;
    static state const BACK_TO_HIVE;


public :
    WorkerBee (Hive& Home, const Vec2d& position);
    ~WorkerBee() {}
    virtual j::Value getConfig() const&;
    virtual void onState (state const& s, sf::Time dt);
    virtual void onEnterState(state const& s)  ;
    void drawOn(sf::RenderTarget& target) const;

};
