#include <iostream>
#include "WorkerBee.hpp"
#include "Application.hpp"

state const WorkerBee::IN_HIVE = createUid() ;
state const WorkerBee::TO_FLOWER  = createUid() ;
state const WorkerBee::NECTAR_COLLECT  = createUid() ;
state const WorkerBee::BACK_TO_HIVE = createUid() ;

WorkerBee::WorkerBee(Hive& Home, const Vec2d& position) :
    Bee(Home, position, getAppConfig().worker_size, getAppConfig().worker_initial_energy, getAppConfig().worker_speed, {IN_HIVE, TO_FLOWER, NECTAR_COLLECT, BACK_TO_HIVE}),
    nectar(0.00)
{}

j::Value WorkerBee::getConfig() const& {
    return getValueConfig()["simulation"]["bees"]["worker"];
}

void WorkerBee::onState (state const& s, sf::Time dt) {
    if (s == IN_HIVE) {
        if (nectar > 0.00) {
            if (nectar - dt.asSeconds()*getAppConfig().worker_transfer_rate > 0.00) {
                dropPollen(dt.asSeconds()*getAppConfig().worker_transfer_rate);
                nectar -= dt.asSeconds()*getAppConfig().worker_transfer_rate;
            }
            else nectar = 0.00;
        }
        else if (nectar == 0.00) {
            if (get_energy() < getAppConfig().worker_energy_to_leave_hive) {
                gain_energy(dt.asSeconds() * getAppConfig().worker_eating_rate);
            }
            else if (get_value_memory() == true) {
                nextState();
            }
        }
    }

    else if (s == TO_FLOWER) {
        if (*this > get_memory()) {
            nextState();
        }
   }

    else if (s == NECTAR_COLLECT) {
        int i(0); // indice de la fleur
        while (get_memory() != getAppEnv().get_flowers()[i]->getPosition()) {
            ++i;
        }

        if (getAppEnv().get_flowers()[i]->get_pollen() != 0.00 and nectar != getAppConfig().worker_pollen_capacity) {
            takePollen(dt.asSeconds()*getAppConfig().worker_harvest_rate, i);
        }
        else nextState();

    }


    else if (s == BACK_TO_HIVE) {
        if (Collider(home_position(), home_radius()) > *this) {
            nextState();
        }
    }
}

void WorkerBee::onEnterState(state const& s) {
    if (s == IN_HIVE) {
        change_mode("au repos");
    }

    else if (s == TO_FLOWER) {
        change_target(get_memory());
        change_value_memory(true);
        change_mode("ciblé");
    }

    else if (s == NECTAR_COLLECT) {
        change_mode("au repos");
        change_value_memory(false);
    }

    else if (s == BACK_TO_HIVE) {
        change_target(home_position());
        change_mode("ciblé");     
    }
}

void WorkerBee::drawOn(sf::RenderTarget& target) const {
    Bee::drawOn(target);

    std::string plus;
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

    if (isDebugOn() == true) {
        auto const text = buildText("Worker: energy <" + to_nice_string(get_energy()) +">", text_position+ Vec2d(0.00, 25.00), getAppFont(), text_size, text_color);
        target.draw(text);
        auto const text2 = buildText(plus, text_position + Vec2d(0.00, 40.00), getAppFont(), text_size, text_color);
        target.draw(text2);
    }
}

void WorkerBee::interact(Bee* other) {
    other->interactWith(this);
}

void WorkerBee::interactWith(ScoutBee* ) {}

void WorkerBee::interactWith(WorkerBee* ) {}


void WorkerBee::takePollen(double qte, int i) {
    double plus (getAppEnv().get_flowers()[i]->takePollen(qte));

    if (nectar + plus > getAppConfig().worker_pollen_capacity) {
        nectar = getAppConfig().worker_pollen_capacity;
    }
    else {
        nectar += plus;
    }
}

state WorkerBee::get_in_hive() {
    return IN_HIVE;
}
