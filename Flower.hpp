#include <iostream>
#include "Collider.hpp"
#include <SFML/Graphics.hpp>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#pragma once

class Flower : public Collider, public Drawable, public Updatable {
private :
    double pollen; // pollen's amount of this Flower
    int const indice; // indice of this Flower's texture


public :

    // CONSTRUCTOR AND DESTRUCTOR
    /*!
     * \brief construct a Flower object fully set up
     * \param position the Flower's position
     * \param arg_diam the Flower's diameter
     * \param arg_pollen the Flower's pollen's amount
     */
    Flower (const Vec2d& position, double arg_diam, double arg_pollen); // constructor

    virtual ~Flower () {} // destructor


    // RELATIVE TO POLLEN
    /*!
     * \brief take a certain amount of pollen to this Flower
     * \param amount the amount wanted to be taken
     * \return the amount of pollen that could have been taken
     */
    double takePollen (double amount);


    // RELATIVE TO EVOLUTION
    /*!
     * \brief draw this Flower
     * \param target the environment where to draw
     */
    void drawOn(sf::RenderTarget& target) const override ;

    /*!
     * \brief update the Flower's evolution
     * \param dt the small amount of time between each evolution
     */
    void update(sf::Time dt) override ;


    // GETTER
    /*!
     * \brief get this Flower's pollen's amount
     * \return this Flower's pollen's amount
     */
    double get_pollen () const;
};
