#include <iostream>
#include "Utility/Utility.hpp"

typedef Uid state;

class CFSM {
private :
    std::vector<state> States;
    int index;

public :
    CFSM (std::vector<state> const& possible_states);
    state getState() const;
    void nextState() ;
    virtual void onEnterState(state const&) = 0;
    virtual void onState (state const& s, sf::Time dt) = 0;
    void action(sf::Time dt) ;
};


