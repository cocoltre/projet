#include <iostream>
#include "Bee.hpp"

#pragma once

class WorkerBee : public Bee {
private :
    static state const IN_HIVE ;            // a particular state : when the bee is in the Hive
    static state const TO_FLOWER ;          // a particular state : when the bee is flying to a Flower
    static state const NECTAR_COLLECT ;     // a particular state : when the bee is collecting nectar
    static state const BACK_TO_HIVE ;       // a particular state : when the bee is flying back to the Hive

    double nectar;          // amount of nectar that has collected this WorkerBee

public :

    // CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
    /*!
     * \brief construct a WorkerBee object fully set up
     * \param Home this WorkerBee's Hive
     * \param position this WorkerBee's position
     */
    WorkerBee (Hive& Home, const Vec2d& position);

    ~WorkerBee() {} // destructor

    /*!
     * \brief get the configuration specific to a WorkerBee
     * \return the j::Value of the WorkerBee's configuration
     */
    virtual j::Value getConfig() const&;


    // RELATIVE TO ACTIONS IN STATES
    /*!
     * \brief do the actions necessary in the specific state
     * \param s the specific state
     * \param dt the small amount of time between each evolution
     */
    virtual void onState (state const& s, sf::Time dt);

    /*!
     * \brief do the actions necessary when entering in the new state
     * \param s the new state
     */
    virtual void onEnterState(state const& s) ;


    // RELATIVE TO EVOLUTION
    /*!
     * \brief draw the WorkerBee
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
     * \brief do the actions necessary when interacting with a ScoutBee
     * \param scouting the ScoutBee
     */
    virtual void interactWith(ScoutBee* scouting) ;

    /*!
     * \brief do the actions necessary when interacting with an other WorkerBee
     * \param working the other WorkerBee
     */
    virtual void interactWith(WorkerBee* working) ;


    // RELATIVE TO POLLEN
    /*!
     * \brief take a certain amount of pollen of a Flower and convert it into nectar
     * \param qte the pollen's amount wanted to be taken of the Flower
     * \param i the index of the Flower in the Flowers' collection of the environment
     */
    void takePollen(double qte, int i) ;


    // GETTER
    /*!
     * \brief get the state IN_HIVE
     * \return the state IN_HIVE
     */
    static state get_in_hive();
};
