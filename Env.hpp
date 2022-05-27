#include <iostream>
#include "World.hpp"
#include "Flower.hpp"
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include "FlowerGenerator.hpp"
#include "Hive.hpp"
#include <unordered_map>
#pragma once

class Env : public Drawable, public Updatable {
private :

    // ATTRIBUTES
    World world;                        // the Env's World
    std::vector <Flower*> Flowers;      // the Env's Flowers' collection
    FlowerGenerator flowergenerator;    // the Env's FlowerGenerator
    std::vector <Hive*> Hives;          // the Env's Hives' collection
    unsigned int nb_scout;              // the number of ScoutBees
    unsigned int nb_worker;             // the number of WorkerBees

    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

    // PRIVATE METHODS

    // CONSTRUCTOR AND DESTRUCTORS
    /*!
     * \brief delete all the flowers' collection
     */
    void delete_flowers ();

    /*!
     * \brief delete all the Hives' collection
     */
    void delete_hives ();


public :

    // CONSTRUCTOR AND DESTRUCTORS
    /*!
     * \brief constructor of an Env object fully set up by default
     */
    Env ();     // constructor by default

    virtual ~Env () {   // destructor
        delete_flowers();       // delete all the Flowers' collection
        delete_hives();         // delete all the Hives' collection
        nb_scout = 0;           // reset the counter of ScoutBees and WorkerBees
        nb_worker = 0;
    }


    // RELATIVE TO EVOLUTION
    /*!
     * \brief update the Env's evolution
     * \param dt the small amount of time between each evolution
     */
    void update(sf::Time dt) override ;

    /*!
     * \brief draw the Env
     * \param target the environment where to draw
     */
    void drawOn(sf::RenderTarget& target) const override ;

    /*!
     * \brief draw a zone around a specific position, whose color determines whether the position can host a new Flower or not
     * \param target the environment where to draw
     * \param position the specific position
     */
    void drawFlowerZone(sf::RenderTarget& target, Vec2d const& position) const;

    /*!
     * \brief draw a zone around a specific position, whose color determines whether the position can host a new Hive or not
     * \param target the environment where to draw
     * \param position the specific position
     */
    void drawHiveableZone(sf::RenderTarget& target, Vec2d const& position) ;

    /*!
     * \brief reset the Env
     */
    void reset();

    /*!
     * \brief reset all controls
     */
    void resetControls();


    // RELATIVE TO FILE MANAGEMENT
    /*!
     * \brief load a World from a file
     */
    void loadWorldFromFile();

    /*!
     * \brief save the World to a specific file
     */
    void saveWorldToFile();


    // GETTERS
    /*!
     * \brief get the Env's World's size
     * \return the Env's World's size
     */
    float getSize () const;

    /*!
     * \brief get the Env's Flowers' collection
     * \return the Env's Flowers' collection
     */
    std::vector <Flower*> get_flowers() const;

    /*!
     * \brief find the humidity of a specific position
     * \param p the specific position
     * \return the humidity of the specific position
     */
    double find_humidity (Vec2d p) const;


    // TESTS
    /*!
     * \brief check if a specific position is made of rocks meaning that a Bee cannot fly there
     * \param p the specific position
     * \return true if the position is rocks
     */
    bool IsFlyable (const Vec2d& p) const ;

    /*!
     * \brief find a Hive in the Env that is colliding with a specific Collider
     * \param body the specific Collider
     * \return a pointer on a Hive colliding with the body, nullptr otherwise
     */
    Hive* getCollidingHive(const Collider& body) const;

    /*!
     * \brief find a Flower in the Env that is colliding with a specific Collider
     * \param body the specific Collider
     * \return a pointer on a flower colliding with the body, nullptr otherwise
     */
    Flower* getCollidingFlower(const Collider& body) const;


    // CHANGE THE ENV
    /*!
     * \brief add a Flower at a specific position if it is possible
     * \param p the specific position
     * \return true if the adding was successful
     */
    bool addFlowerAt (const Vec2d& p);

    /*!
     * \brief add a Hive at a specific position if it is possible
     * \param position the specific position
     * \return true if the adding was successful
     */
    bool addHiveAt(const Vec2d& position);


    // STATS
    /*!
     * \brief create a collection of all the latest dats for all the label's series
     * \param label the specific label
     * \return the collection of all the latest dats for all the label's series
     */
    std::unordered_map<std::string, double> fetchData(std::string label);

    /*!
     * \brief change the number of ScoutBees
     * \param a the adding number
     */
    void change_nb_scout(int a);

    /*!
     * \brief change the number of WorkerBees
     * \param b the adding number
     */
    void change_nb_worker(int b);
};
