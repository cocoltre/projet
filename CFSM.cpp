#include <iostream>
#include "CFSM.hpp"

CFSM::CFSM (std::vector<state> const& possible_states) : States(possible_states), index(0) {
}

state CFSM::getState() const {
    return States[index];
}

void CFSM::nextState() {
    if (index != (int)States.size() - 1) {
        ++ index;
    }
    else index = 0;

    onEnterState(States[index]);
}

void CFSM::action(sf::Time dt) {
    onState(getState(), dt);
}
