#include <iostream>
#include "Bee.hpp"

#pragma once

class WorkerBee : public Bee {
private :
    static state const IN_HIVE;

public :
    WorkerBee (Hive& Home, const Vec2d& position);
    ~WorkerBee() {}
    virtual j::Value getConfig() const&;

};
