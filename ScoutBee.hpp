#include <iostream>
#include "Bee.hpp"

#pragma once

class ScoutBee : public Bee {
private :
    static state const IN_HIVE  ;
    static state const FLOWERS_SEARCH  ;
    static state const BACK_TO_HIVE ;

public :
    ScoutBee(const Hive& Home, const Vec2d& position);
    ~ScoutBee() {}
    virtual j::Value getConfig() const&;

};
