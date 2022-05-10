#include <iostream>
#include "CFSM.hpp"

CFSM::CFSM (std::vector<state> const& possible_states) : States(possible_states), index(0) {}

state CFSM::getState() const {
    return States[index];
}

void CFSM::nextState() {
    onEnterState(States[index]);
    ++ index;

}

void CFSM::onEnterState(state const& s) const {

}

void CFSM::onState (state const& s, sf::Time dt) const {}

void CFSM::action(sf::Time dt) const {
    onState(States[index], dt);
}
