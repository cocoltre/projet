#include <iostream>
#include "WorkerBee.hpp"
#include "Application.hpp"

state const WorkerBee::IN_HIVE = createUid();

WorkerBee::WorkerBee(Hive& Home, const Vec2d& position) :
    Bee(Home, position, getAppConfig().worker_size, getAppConfig().worker_initial_energy, getAppConfig().worker_speed, {IN_HIVE}, nullptr) { }

j::Value WorkerBee::getConfig() const& {
    return getValueConfig()["simulation"]["bees"]["worker"];
}
