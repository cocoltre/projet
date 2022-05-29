#include <iostream>
#include <SFML/Graphics.hpp>
#include "Interface/Updatable.hpp"

#pragma once

class FlowerGenerator : public Updatable {
private :
    sf::Time counter; // the counter


public :

    // CONSTRUCTOR AND DESTRUCTOR
    /*!
     * \brief construct a FlowerGenerator object by default
     */
    FlowerGenerator () {counter = sf::Time::Zero;} // constructor by default

    ~FlowerGenerator () {} // destructor


    // RELATIVE TO EVOLUTION
    /*!
     * \brief update the counter and the generator of Flowers
     * \param dt the small amount of time between each evolution
     */
    void update(sf::Time dt) override ;

    /*!
     * \brief reset the counter
     */
    void reset();
};
