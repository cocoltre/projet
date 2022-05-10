/*
 * POOSV EPFL 2022
 * @authors: 
 */

#pragma once

#include <Utility/Vec2d.hpp>
#include <ostream>
#pragma once

class Collider
{
private :
    Vec2d center;
    double radius;

public :
    Collider (Vec2d position, double arg_radius); // constructeur
    Collider& operator= (Collider const&) = default; // opérateur =
    Collider (Collider const& other); // constructeur de copie
    ~Collider () {}; // destructeur

    Vec2d clamp (const Vec2d& vec);
    Vec2d directionTo (const Vec2d& to) const;
    Vec2d directionTo (const Collider& to) const;
    double distanceTo (const Vec2d& to) const;
    double distanceTo (const Collider& to) const;
    void move (const Vec2d& dx);
    void operator+= (const Vec2d& position2);

    bool isColliderInside (const Collider& other) const;
    bool isColliding (const Collider& other) const;
    bool isPointInside (const Vec2d& point) const;

    bool operator> (const Collider& body2) const;
    bool operator| (const Collider& body2) const;
    bool operator> (const Vec2d& point) const;

    Vec2d getPosition () const;
    double getRadius () const;
};

std::ostream& operator<< (std::ostream& sortie, Collider const& body);
