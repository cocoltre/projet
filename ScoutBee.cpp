#include <iostream>
#include "ScoutBee.hpp"
#include "Application.hpp"

state const ScoutBee::IN_HIVE = createUid();
state const ScoutBee::FLOWERS_SEARCH = createUid();
state const ScoutBee::BACK_TO_HIVE = createUid();


ScoutBee::ScoutBee(Hive& Home, const Vec2d& position) :
    Bee(Home, position, getAppConfig().scout_size, getAppConfig().scout_initial_energy, getAppConfig().scout_speed, {IN_HIVE, FLOWERS_SEARCH, BACK_TO_HIVE}) {}

j::Value ScoutBee::getConfig() const& {
    return getValueConfig()["simulation"]["bees"]["scout"];
}

void ScoutBee::onEnterState(state const& s)  {
    if (s == IN_HIVE) {
        change_mode("au repos");
    }
    else if (s == FLOWERS_SEARCH) {
        change_value_memory();
        change_mode("aléatoire");
    }
    else if (s == BACK_TO_HIVE) {
        change_target(home_position());
        change_mode("ciblé");

    }
}

void ScoutBee::onState (state const& s, sf::Time dt) {
    if (s == IN_HIVE) {
        if (get_energy() < getAppConfig().scout_energy_to_leave_hive) {
            gain_energy(dt.asSeconds() * getAppConfig().scout_eating_rate);
        }
        else if (get_value_memory() == false) {
            nextState();
        }
    }
    else if (s == FLOWERS_SEARCH) {
        std::vector<Flower*> vec;
        for (size_t i(0); i < getAppEnv().get_flowers().size(); ++i) {
            if (*(getAppEnv().get_flowers()[i]) | Collider(getPosition(), getRadius() + getConfig()["visibility range"].toDouble())) {
                vec.push_back(getAppEnv().get_flowers()[i]);
            }
        }
        Flower* maxpollen(nullptr);
        if (vec.size() != 0) {
            maxpollen = vec[0];
            for (size_t i(0); i < vec.size(); ++i) {
                if (vec[i]->get_pollen() > maxpollen->get_pollen()) {
                    maxpollen = vec[i];
                }
            }
        }
        change_memory(*getCollidingFlowerPosition(*maxpollen));
    }
    else if ((s == BACK_TO_HIVE) and (Collider(home_position(), home_radius()) > *this)) {
        nextState();

    }
}

Vec2d const* ScoutBee::getCollidingFlowerPosition(Collider const& body) {
    return new Vec2d(body.getPosition());
}
