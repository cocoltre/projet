#include <iostream>
#include "ScoutBee.hpp"
#include "Application.hpp"
#include "WorkerBee.hpp"

state const ScoutBee::IN_HIVE = createUid();            // create a unique Uid for the state IN_HIVE
state const ScoutBee::FLOWERS_SEARCH = createUid();     // create a unique Uid for the state FLOWER_SEARCH
state const ScoutBee::BACK_TO_HIVE = createUid();       // create a unique Uid for the state BACK_TO_HIVE


// CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
ScoutBee::ScoutBee(Hive& Home, const Vec2d& position) :     // constructor
    Bee(Home, position, getAppConfig().scout_size, getAppConfig().scout_initial_energy, getAppConfig().scout_speed, {IN_HIVE, FLOWERS_SEARCH, BACK_TO_HIVE}),
    n(0)
{}

j::Value ScoutBee::getConfig() const& {                     // get ScoutBee's configuration
    return getValueConfig()["simulation"]["bees"]["scout"];
}


// RELATIVE TO ACTIONS IN STATES
void ScoutBee::onEnterState(state const& s)  {              // do the actions necessary when entering in the new state
    if (s == IN_HIVE) {
        n = 0;
        change_mode("at rest");
    }
    else if (s == FLOWERS_SEARCH) {
        change_value_memory(false);
        change_mode("randomly");
    }
    else if (s == BACK_TO_HIVE) {
        change_target(home_position());
        change_mode("targeted");
    }
}

void ScoutBee::onState (state const& s, sf::Time dt) {      // do the actions necessary in the specific state

    if (s == IN_HIVE) {
        if (get_energy() < getAppConfig().scout_energy_to_leave_hive) {     // when the Bee's energy is too low
            gain_energy(dt.asSeconds() * getAppConfig().scout_eating_rate);
        }
        else if (get_value_memory() == false or n>=1) {                     // when the Bee has shared the information
            nextState();
        }
    }
    else if (s == FLOWERS_SEARCH) {
        if (get_energy() >= getAppConfig().scout_energy_seek_flowers) {     // when the Bee has enough energy
            std::vector<Flower*> vec;                                       // vector of all Flowers in the Bee's visibility range
            Collider c_ = Collider(getPosition(), getRadius() + getConfig()["visibility range"].toDouble());
            for (size_t i(0); i < getAppEnv().get_flowers().size(); ++i) {
                if (*(getAppEnv().get_flowers()[i]) | c_) {
                    vec.push_back(getAppEnv().get_flowers()[i]);
                }
            }
            Flower* maxpollen(nullptr);
            if (vec.size() != 0) {
                maxpollen = vec[0];
                for (size_t i(0); i < vec.size(); ++i) {                    // in order to find the Flower with the biggest amount of pollen
                    if (vec[i]->get_pollen() > maxpollen->get_pollen()) {
                        maxpollen = vec[i];
                       }
                    }
                change_memory(*getCollidingFlowerPosition(*maxpollen));
                change_value_memory(true);
                nextState();
            }
        }
        else { nextState(); }                                               // when the Bee has not enough energy
    }
    else if (s == BACK_TO_HIVE) {
        if (Collider(home_position(), home_radius()) > *this) {             // when the Bee is in the Hive
            nextState();
        }
    }
}


// RELATIVE TO EVOLUTION
void ScoutBee::drawOn(sf::RenderTarget& target) const {     // draw a ScoutBee
    Bee::drawOn(target);

    std::string plus;                                       // indicate the Bee's action
    int text_size (15);
    sf::Color text_color(sf::Color::White);
    Vec2d text_position (getPosition());

    if (getState() == IN_HIVE) {
        if (get_energy() < getAppConfig().scout_energy_to_leave_hive) {
            plus = "in_hive_eat";
        }

        else if (get_value_memory() == false or n>=1) {
            plus = "in_hive_leaving";
        }

        else {
            plus = "in_hive_sharing[" + to_nice_string(n) + ']';
        }
    }
    else if (getState() == FLOWERS_SEARCH) {
        plus = "seeking_flower";
    }
    else if (getState() == BACK_TO_HIVE) {
        plus = "back_to_hive";
    }

    if (isDebugOn() == true) {                              // debugging option
        auto const text = buildText("Scout: energy <" + to_nice_string(get_energy()) +">", text_position+ Vec2d(0.00, 25.00), getAppFont(), text_size, text_color);
        target.draw(text);
        auto const text2 = buildText(plus, text_position + Vec2d(0.00, 40.00), getAppFont(), text_size, text_color);
        target.draw(text2);
    }
}


// RELATIVE TO INTERACTIONS
void ScoutBee::interact(Bee* other) {                       // do the actions necessary when interacting with an other Bee
    other->interactWith(this);
}

void ScoutBee::interactWith(ScoutBee* ) {}                  // no interaction with a ScoutBee

void ScoutBee::interactWith(WorkerBee* working) {           // do the actions necessary when interacting with a WorkerBee
    if (get_value_memory() and n < getAppConfig().scout_max_sharing) {
        working->change_memory(get_memory());
        working->change_value_memory(true);
        ++n;
    }
}


// GETTERS
Vec2d const* ScoutBee::getCollidingFlowerPosition(Collider const& body) const {     // create a pointer on the position of the Colliding Flower
    return new Vec2d(body.getPosition());
}

state ScoutBee::get_in_hive() const {                                               // get the state IN_HIVE
    return IN_HIVE;
}




