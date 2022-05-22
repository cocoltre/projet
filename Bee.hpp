#include <iostream>
#include "Hive.hpp"
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "CFSM.hpp"
#pragma once

class ScoutBee;     // predeclaration
class WorkerBee;    // predeclaration

class Bee: public Collider, public Drawable, public Updatable, public CFSM {
private:
    Hive& Home;                 // the Bee's Hive
    Vec2d speed;                // the Bee's speed
    double energy;              // the Bee's energy
    Vec2d memory;               // the Bee's memory (the Flower it has in memory)
    bool memory_value;          // the memory's value (true if it ithe Bee has a Flower in memory, false if it the Bee has no Flower in memory)
    std::string mode;           // the Bee's mode
    Vec2d target;               // the Bee's target
    sf::Time avoidanceClock_;   // the avoidance clock when the Bee is blocked by rocks


public:

    // CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
    /*!
     * \brief construct a Bee object fully set up
     * \param Home the Bee's Hive
     * \param position the Bee's position
     * \param arg_rad the Bee's radius
     * \param energy2 the Bee's energy
     * \param ScalSpeed the Bee's speed
     * \param possible_states the Bee's collection of states
     */
    Bee(Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states);

    virtual ~Bee () {} // destructor

    /*!
     * \brief get the configuration specific to a Bee
     * \return the j::Value of the Bee's configuration
     */
    virtual j::Value getConfig() const& = 0 ;


    // MOVEMENT
    /*!
     * \brief move the Bee during a small amount of time
     * \param dt the small amount of time
     */
    void move(sf::Time dt);

    /*!
     * \brief move the Bee in a precise direction during a small amount of time
     * \param dt the small amount of time
     */
    void targetMove(sf::Time dt);

    /*!
     * \brief move the Bee in a random way during a small amount of time
     * \param dt the small amount of time
     */
    void randomMove(sf:: Time dt);


    // RELATIVE TO EVOLUTION
    /*!
     * \brief check if the Bee is dead (when it has no energy)
     * \return true if the Bee is dead
     */
    bool Isdead () const;

    /*!
     * \brief draw the Bee
     * \param target the environment where to draw
     */
    virtual void drawOn(sf::RenderTarget& target) const;

    /*!
     * \brief update the Bee's evolution
     * \param dt the small amount of time
     */
    void update(sf::Time dt);


    // GETTERS
    /*!
     * \brief get the Bee's energy
     * \return the Bee's energy
     */
    double get_energy() const;

    /*!
     * \brief check if the Bee's memory's value is correct
     * \return true if the memory's value is correct (if the Bee has a Flower in memory)
     */
    bool get_value_memory() const;

    /*!
     * \brief get the Bee's memory
     * \return the Bee's memory
     */
    Vec2d get_memory() const;

    /*!
     * \brief get the Bee's Hive's position
     * \return the Bee's Hive's position
     */
    Vec2d home_position () const ;

    /*!
     * \brief get the Bee's Hive's radius
     * \return the Bee's Hive's radius
     */
    double home_radius() const ;


    // RELATIVE TO ACTIONS IN STATES
    /*!
     * \brief do the actions necessary in the specific state
     * \param s the specific state
     * \param dt the small amount of time between each evolution
     */
    virtual void onState (state const& s, sf::Time dt) = 0;

    /*!
     * \brief do the actions necessary when entering in the new state
     * \param s the new state
     */
    virtual void onEnterState(state const& s) = 0;


    // CHANGERS
    /*!
     * \brief change the Bee's mode
     * \param newmode the new mode
     */
    void change_mode(std::string newmode);

    /*!
     * \brief change the Bee's target
     * \param newtarget the new target
     */
    void change_target(Vec2d const& newtarget);

    /*!
     * \brief change the Bee's memory
     * \param newmemory the new memory
     */
    void change_memory(Vec2d const& newmemory);

    /*!
     * \brief change the Bee's memory's value
     * \param b the new memory's value
     */
    void change_value_memory(bool b);

    /*!
     * \brief convert a certain amount of nectar into energy to the Bee
     * \param qte the amount of nectar
     */
    void gain_energy(double qte);

    /*!
     * \brief learn a new Flower's Position
     * \param flowerPosition the Flower's position
     */
    void learnFlowerLocation(const Vec2d& flowerPosition);


    // RELATIVE TO POLLEN
    /*!
     * \brief drop a certain amount of pollen in the Bee's Hive
     * \param qte the certain amount of pollen
     */
    void dropPollen(double qte) ;


    // RELATIVE TO INTERACTIONS
    /*!
     * \brief do the actions necessary when interacting with an other Bee
     * \param other an other Bee
     */
    virtual void interact(Bee* other) = 0;

    /*!
     * \brief do the actions necessary when interacting with an other ScoutBee
     * \param scouting a ScoutBee
     */
    virtual void interactWith(ScoutBee* scouting) = 0;

    /*!
     * \brief do the actions necessary when interacting with a WorkerBee
     * \param working a WorkerBee
     */
    virtual void interactWith(WorkerBee* working) = 0;

};
