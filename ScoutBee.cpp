#include <iostream>
#include "ScoutBee.hpp"
#include "Application.hpp"

state const ScoutBee::IN_HIVE = createUid();
state const ScoutBee::FLOWERS_SEARCH = createUid();
state const ScoutBee::BACK_TO_HIVE = createUid();


ScoutBee::ScoutBee(const Hive& Home, const Vec2d& position) :
    Bee(Home, position, getAppConfig().scout_size, getAppConfig().scout_initial_energy, getAppConfig().scout_speed, {IN_HIVE, FLOWERS_SEARCH, BACK_TO_HIVE}, nullptr) {}

j::Value ScoutBee::getConfig() const& {
    return getValueConfig()["simulation"]["bees"]["scout"];
}

