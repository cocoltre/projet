#include <iostream>
#include "WorkerBee.hpp"
#include "Application.hpp"
#include "Bee.hpp"
#include "Hive.hpp"

state const WorkerBee::IN_HIVE = createUid();
state const WorkerBee::TO_FLOWER = createUid();
state const WorkerBee::COLLECT_POLLEN = createUid();
state const WorkerBee::BACK_TO_HIVE = createUid();

WorkerBee::WorkerBee(Hive& Home, const Vec2d& position) :
    Bee(Home, position, getAppConfig().worker_size, getAppConfig().worker_initial_energy, getAppConfig().worker_speed, {IN_HIVE}) { }

j::Value WorkerBee::getConfig() const& {
    return getValueConfig()["simulation"]["bees"]["worker"];
}

void WorkerBee::onEnterState(state const& s)  {
    if (s == IN_HIVE) {
        change_mode("au repos");
    }else if (s == TO_FLOWER) {
        Vec2d f;
        change_target(learnFlowerLocation(f));
        change_mode("ciblé");
    }else if (s==COLLECT_POLLEN){
        change_mode("au repos");
    }else if (s == BACK_TO_HIVE) {
        change_target(home_position());
        change_mode("ciblé");
    }
}

void WorkerBee::onState (state const& s, sf::Time dt) {
    if (s == IN_HIVE) {
        if (get_pollen()>0.00){
            dropPollen(dt.asSeconds()*getAppConfig().worker_transfer_rate);
        }else if(get_pollen()==0.00){
            if (get_energy() < getAppConfig().scout_energy_to_leave_hive) {
                gain_energy(dt.asSeconds() * getAppConfig().worker_eating_rate);
            }else if (get_value_memory() == true) {
                nextState();
            }
        }
    }else if (s==TO_FLOWER){
        if (Collider(learnFlowerLocation()))

        nextState();
    }else if (s==COLLECT_POLLEN){
              if (get_pollen()<getAppConfig().worker_pollen_capacity){
                  takePollen(dt.asSeconds()*getAppConfig().worker_harvest_rate);
                  nextState();
              }
    }else if (s == BACK_TO_HIVE){
        if (Collider(home_position(), home_radius()) > *this) {
            nextState();
        }
    }
}

void Hive::drawOn(sf::RenderTarget& targetWindow) const {
    int text_size (30);
    sf::Color text_color(sf::Color::Black);
    Vec2d text_position (getPosition().x(), getPosition().y()+3);

    if (isDebugOn() == true) {
        auto const text = "Worker: energy" + buildText(to_nice_string(energy), text_position, getAppFont(), text_size, text_color);
        targetWindow.draw(text);

    }
}
