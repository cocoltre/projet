#include <iostream>
#include "Utility/Utility.hpp"

typedef Uid state;

class CFSM {
private :
    std::vector<state> States; // the collection of states
    int index;  // index of the current state

public :

    // CONSTRUCTOR AND DESTRUCTOR
    /*!
     * \brief construct a CFSM object fully set up
     * \param possible_states the collection of states
     */
    CFSM (std::vector<state> const& possible_states);

    virtual ~CFSM () {}  // destructor


    // GETTER
    /*!
     * \brief get the current state
     * \return the current state
     */
    state getState() const;


    // RELATIVE TO ACTIONS IN STATES
    /*!
     * \brief change to the next state
     */
    void nextState();

    /*!
     * \brief do the actions necessary when entering in a new state
     */
    virtual void onEnterState(state const&) = 0;

    /*!
     * \brief do the actions necessary in a specific state
     */
    virtual void onState (state const&, sf::Time) = 0;

    /*!
     * \brief do all the actions necessary in the current state
     * \param dt the small amount of time
     */
    void action(sf::Time dt);
};


