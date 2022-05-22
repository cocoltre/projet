#include <iostream>
#include <vector>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once

class Bee; // predeclaration

class Hive : public Collider, public Drawable, public Updatable {
private :
    std::vector<Bee*> Bees; // this Hive's Bees' collection
    double pollen;          // the nectar's amount that contains this Hive

public :

    // CONSTRUCTORS AND DESTRUCTORS
    /*!
     * \brief construct a Hive object fully set up
     * \param position this Hive's position
     * \param arg_radius this Hive's radius
     */
    Hive (Vec2d position, double arg_radius);

    /*!
     * \brief delete the copy's constructor
     * \param temp_obj an other Hive that wants to be copied
     */
    Hive(const Hive& temp_obj) = delete;

    /*!
     * \brief delete the copy's operator
     * \param temp_obj an other Hive that wants to be copied
     * \return normally a Hive
     */
    Hive& operator=(const Hive& temp_obj) = delete;

    ~Hive () {              // destructor
        delete_bees();      // destroy all the Bees the Hive contains
    }

    /*!
     * \brief delete all the Bees' collection
     */
    void delete_bees ();


    // RELATIVE TO EVOLUTION
    /*!
     * \brief update the Hive's evolution
     * \param dt the small amount of time between each evolution
     */
    void update(sf::Time dt);

    /*!
     * \brief draw the Hive
     * \param targetWindow the environment where to draw
     */
    void drawOn(sf::RenderTarget& targetWindow) const;


    // RELATIVE TO POLLEN/NECTAR
    /*!
     * \brief drop a certain amount of nectar in the Hive
     * \param qte the certain amount
     */
    void dropPollen(double qte);

    /*!
     * \brief take a certain amount of nectar of the Hive
     * \param qte the certain amount of nectar
     * \return the amount of nectar that could have been taken
     */
    double takeNectar(double qte);

protected :

    // RELATIVE TO BEES
    /*!
     * \brief add a Bee to this Hive
     * \param scoutProb the probability for the new Bee to be a ScoutBee
     * \return a pointer on the new Bee
     */
    Bee* addBee(double scoutProb=0);

};
