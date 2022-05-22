#include <iostream>
#include "Bee.hpp"

#pragma once

class ScoutBee : public Bee {
private :
    static state const IN_HIVE ;        // a particular state : when the bee is in the Hive
    static state const FLOWERS_SEARCH ; // a particular state : when the bee is searching flowers
    static state const BACK_TO_HIVE;    // a particular state : when the bee is flying back to the Hive

    int n; // number of bees with whom this ScoutBee has shared the information of a flower

public :

    // CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
    /*!
     * \brief construct a ScoutBee object fully set up
     * \param Home this ScoutBee's Hive
     * \param position this ScoutBee's position
     */
    ScoutBee(Hive& Home, const Vec2d& position);

    ~ScoutBee() {} // destructor

    /*!
     * \brief get the configuration specific to a ScoutBee
     * \return the j::Value of the ScoutBee's configuration
     */
    virtual j::Value getConfig() const&;


    // RELATIVE TO ACTIONS IN STATES
    /*!
     * \brief do the actions necessary when entering in the new state
     * \param s the new state
     */
    virtual void onEnterState(state const& s);

    /*!
     * \brief do the actions necessary in the specific state
     * \param s the specific state
     * \param dt the small amount of time between each evolution
     */
    virtual void onState (state const& s, sf::Time dt);


    // RELATIVE TO EVOLUTION
    /*!
     * \brief draw the ScoutBee
     * \param target the environment where to draw
     */
    virtual void drawOn(sf::RenderTarget& target) const;


    // RELATIVE TO INTERACTIONS
    /*!
     * \brief do the actions necessary when interacting with an other Bee
     * \param other the other Bee
     */
    virtual void interact(Bee* other) ;

    /*!
     * \brief do the actions necessary when interacting with an other ScoutBee
     * \param scouting the other ScoutBee
     */
    virtual void interactWith(ScoutBee* scouting) ;

    /*!
     * \brief do the actions necessary when interacting with a WorkerBee
     * \param working a WorkerBee
     */
    virtual void interactWith(WorkerBee* working) ;


    // GETTERS
    /*!
     * \brief create a pointer on the position of the Colliding Flower
     * \param body the colliding flower
     * \return a pointer on the position of the Colliding Flower
     */
    Vec2d const* getCollidingFlowerPosition(Collider const& body);

    /*!
     * \brief get the state IN_HIVE
     * \return the state IN_HIVE
     */
    static state get_in_hive() ;
};
