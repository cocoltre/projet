#include <iostream>
#include "WorkerBee.hpp"
#include "Application.hpp"

state const WorkerBee::IN_HIVE = createUid() ;              // create a unique Uid for the state IN_HIVE
state const WorkerBee::TO_FLOWER  = createUid() ;           // create a unique Uid for the state TO_FLOWER
state const WorkerBee::NECTAR_COLLECT  = createUid() ;      // create a unique Uid for the state NECTAR_COLLECT
state const WorkerBee::BACK_TO_HIVE = createUid() ;         // create a unique Uid for the state BACK_TO_HIVE


// CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
WorkerBee::WorkerBee(Hive& Home, const Vec2d& position) :       // constructor
    Bee(Home, position, getAppConfig().worker_size, getAppConfig().worker_initial_energy, getAppConfig().worker_speed, {IN_HIVE, TO_FLOWER, NECTAR_COLLECT, BACK_TO_HIVE}),
    nectar(0.00)
{}

j::Value WorkerBee::getConfig() const& {                        // get the configuration specific to a WorkerBee
    return getValueConfig()["simulation"]["bees"]["worker"];
}


// RELATIVE TO ACTIONS IN STATES
void WorkerBee::onState (state const& s, sf::Time dt) {         // do the actions necessary in the specific state
    if (s == IN_HIVE) {
        if (nectar > 0.00) {                                    // when the Bee enters in the hive with nectar collected
            if (nectar - dt.asSeconds()*getAppConfig().worker_transfer_rate > 0.00) {       // nectar's sharing to the Hive
                dropPollen(dt.asSeconds()*getAppConfig().worker_transfer_rate);
                nectar -= dt.asSeconds()*getAppConfig().worker_transfer_rate;
            }
            else nectar = 0.00;
        }
        else if (nectar == 0.00) {                              // when the Bee has shared all the nectar it had collected
            if (get_energy() < getAppConfig().worker_energy_to_leave_hive) {                // when the Bee's energy is too low
                gain_energy(dt.asSeconds() * getAppConfig().worker_eating_rate);
            }
            else if (get_value_memory() == true) {              // when the WorkerBee has been shared an information of a Flower
                nextState();
            }
        }
    }

    else if (s == TO_FLOWER) {
        if (*this > get_memory()) {                             // when the Bee has found the Flower
            nextState();
        }
    }

    else if (s == NECTAR_COLLECT) {
        int i(0);                                               // Flower's index in the Flower's collection of the environment
        while (get_memory() != getAppEnv().get_flowers()[i]->getPosition()) {               // find the right index
            ++i;
        }

        if (getAppEnv().get_flowers()[i]->get_pollen() != 0.00 and nectar != getAppConfig().worker_pollen_capacity) {   // collect nectar
            takePollen(dt.asSeconds()*getAppConfig().worker_harvest_rate, i);
        }
        else nextState();
    }

    else if (s == BACK_TO_HIVE) {
        if (Collider(home_position(), home_radius()) > *this) {     // when the Bee is in the Hive
            nextState();
        }
    }
}

void WorkerBee::onEnterState(state const& s) {                      // do the actions necessary when entering in the new state
    if (s == IN_HIVE) {
        change_mode("at rest");
    }

    else if (s == TO_FLOWER) {
        change_target(get_memory());
        change_value_memory(true);
        change_mode("targeted");
    }

    else if (s == NECTAR_COLLECT) {
        change_mode("at rest");
        change_value_memory(false);
    }

    else if (s == BACK_TO_HIVE) {
        change_target(home_position());
        change_mode("targeted");
    }
}


// RELATIVE TO EVOLUTION
void WorkerBee::drawOn(sf::RenderTarget& target) const {            // draw a WorkerBee
    Bee::drawOn(target);

    std::string plus;                                               // indicate the Bee's action
    int text_size (15);
    sf::Color text_color(sf::Color::Yellow);
    Vec2d text_position (getPosition());

    if (getState() == IN_HIVE) {
        if (nectar != 0.00) {
            plus = "in_hive_pollen";
        }

        else if (get_energy() < getAppConfig().scout_energy_to_leave_hive) {
            plus = "in_hive_eat";
        }

        else if (get_value_memory() == false) {
            plus = "in_hive_no_flower";
        }

        else {
            plus = "in_hive_???";
        }
    }

    else if (getState() == TO_FLOWER) {
        plus = "to_flower";
    }

    else if (getState() == NECTAR_COLLECT) {
        plus = "collecting_pollen";
    }

    else if (getState() == BACK_TO_HIVE) {
        plus = "back_to_hive";
    }

    if (isDebugOn() == true) {                          // debugging option
        auto const text = buildText("Worker: energy <" + to_nice_string(get_energy()) +">", text_position+ Vec2d(0.00, 25.00), getAppFont(), text_size, text_color);
        target.draw(text);
        auto const text2 = buildText(plus, text_position + Vec2d(0.00, 40.00), getAppFont(), text_size, text_color);
        target.draw(text2);
    }
}


// RELATIVE TO INTERACTIONS
void WorkerBee::interact(Bee* other) {                  // do the actions necessary when interacting with an other Bee
    other->interactWith(this);
}

void WorkerBee::interactWith(ScoutBee* ) {}             // interaction with ScoutBees already created by the ScoutBees

void WorkerBee::interactWith(WorkerBee* ) {}            // no interaction with an other WorkerBee


// RELATIVE TO POLLEN
void WorkerBee::takePollen(double qte, int i) {         // take a certain amount of pollen of a Flower and convert it into nectar
    double plus (getAppEnv().get_flowers()[i]->takePollen(qte));        // pollen's amount that could have been taken

    if (nectar + plus > getAppConfig().worker_pollen_capacity) {
        nectar = getAppConfig().worker_pollen_capacity;
    }
    else {
        nectar += plus;
    }
}


// GETTER
state WorkerBee::get_in_hive() const {                                  // get the state IN_HIVE
    return IN_HIVE;
}
