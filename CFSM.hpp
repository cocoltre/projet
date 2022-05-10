#include <iostream>
#include "Utility/Utility.hpp"

typedef Uid state;

class CFSM {
private :
    std::vector<state> const& States;
    int index;

public :
    CFSM (std::vector<state> const& possible_states);
    state getState() const;
    void nextState() ;
    void onEnterState(state const& s) const;
    void onState (state const& s, sf::Time dt) const;
    void action(sf::Time dt) const;
};


