#include <iostream>
#include "CFSM.hpp"

// CONSTRUCTOR AND DESTRUCTOR
CFSM::CFSM (std::vector<state> const& possible_states) : States(possible_states), index(0) {} // constructor


// GETTER
state CFSM::getState() const {              // get the current state
    return States[index];
}


// RELATIVE TO ACTIONS IN STATES
void CFSM::nextState() {                    // do the actions necessary when entering a new state
    if (index != (int)States.size() - 1) {  // change the index
        ++ index;
    }
    else index = 0;

    onEnterState(States[index]);            // do the actions necessary
}

void CFSM::action(sf::Time dt) {            // do all the actions necessary in the current state
    onState(getState(), dt);
}
