#include <iostream>
#include "CFSM.hpp"

CFSM::CFSM (std::vector<state> const& possible_states) : States(possible_states), index(0) {}

state CFSM::getState() const {
    return States[index];
}

void CFSM::nextState() {
    onEnterState(States[index]);
    if (index != (int)States.size() - 1) {
        ++ index;
    }
    else { index = 0; }
}

void CFSM::onEnterState(state const& s) {}

void CFSM::onState (state const& s, sf::Time dt) {}

void CFSM::action(sf::Time dt) {
    onState(States[index], dt);
}
