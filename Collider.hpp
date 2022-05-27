/*
 * POOSV EPFL 2022
 * @authors: 
 */

#include <Utility/Vec2d.hpp>
#include <ostream>
#pragma once

class Collider {
private :

    // ATTRIBUTES

    Vec2d center; // center of the Collider
    double radius; // radius of the Collider

    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

    // PRIVATE METHOD

    // MOVEMENT
    /*!
     * \brief clamp a position in the toric world
     * \param vec the initial position
     * \return the new position adapted to the toric world
     */
    Vec2d clamp (const Vec2d& vec);


public :

    // OPERATORS AND DESTRUCTOR
    /*!
     * \brief construct a Collider object fully set up
     * \param position the Collider's center's position
     * \param arg_radius the Collider's radius
     */
    Collider (Vec2d position, double arg_radius); // constructor

    Collider& operator= (Collider const&) = default; // operator =

    /*!
     * \brief construct a Collider object identitical to an other
     * \param other other Collider
     */
    Collider (Collider const& other); // copy's constructor

    virtual ~Collider () {} // destructor


    // MOVEMENT
    /*!
     * \brief find the shortest way in the toric world to go to a specific place
     * \param to the specific place
     * \return the shortest vector to go to the specific place
     */
    Vec2d directionTo (const Vec2d& to) const;

    /*!
     * \brief find the shortest way in the toric world to go to the position of a specific Collider from this Collider
     * \param to the position of the specific Collider
     * \return the shortest vector in the toric world to go to the position of the specific Collider from this Collider
     */
    Vec2d directionTo (const Collider& to) const;

    /*!
     * \brief calculate the distance of this Collider to a specific place
     * \param to the specific place
     * \return the distance of this Collider to the specific place
     */
    double distanceTo (const Vec2d& to) const;

    /*!
     * \brief calculate the distance of this Collider to the position of a specific Collider
     * \param to the position of the specific Collider
     * \return the distance of this Collider to the position of the specific Collider
     */
    double distanceTo (const Collider& to) const;

    /*!
     * \brief move the center of this Collider from a vector in the toric world
     * \param dx the vector added
     */
    void move (const Vec2d& dx);

    /*!
     * \brief create an operator that moves the center of this Collider from a vector in the toric world
     * \param position2 the vector added
     */
    void operator+= (const Vec2d& position2);


    // TESTS
    /*!
     * \brief check if a Collider is inside this Collider
     * \param other an other Collider
     * \return true if the Collider is inside this Collider
     */
    bool isColliderInside (const Collider& other) const;

    /*!
     * \brief check if a Collider is colliding with this Collider
     * \param other an other Collider
     * \return true if the Collider is colliding with this Collider
     */
    bool isColliding (const Collider& other) const;

    /*!
     * \brief check if a point is inside this Collider
     * \param point a point
     * \return true if the point is inside this Collider
     */
    bool isPointInside (const Vec2d& point) const;

    /*!
     * \brief create an operator that checks if a Collider is inside this Collider
     * \param body2 an other Collider
     * \return true if the point is inside this Collider
     */
    bool operator> (const Collider& body2) const;

    /*!
     * \brief create an operator that checks if a Collider is colliding with this Collider
     * \param body2 an other Collider
     * \return true if the Collider is colliding with this Collider
     */
    bool operator| (const Collider& body2) const;

    /*!
     * \brief create an operator that checks if a point is inside this Collider
     * \param point a point
     * \return true if the point is inside this Collider
     */
    bool operator> (const Vec2d& point) const;


    // GETTERS
    /*!
     * \brief get this Collider's position
     * \return this Collider's position
     */
    Vec2d getPosition () const;

    /*!
     * \brief get this Collider's radius
     * \return this Collider's radius
     */
    double getRadius () const;

};

std::ostream& operator<< (std::ostream& sortie, Collider const& body); // extern operator that shows a Collider's information
