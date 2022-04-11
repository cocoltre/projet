/*
 * POOSV EPFL 2022
 * @authors: 
 */

#pragma once

#include <Utility/Vec2d.hpp>
#include <ostream>
#include <Application.hpp>


class Collider
{
private :
    Vec2d center;
    double radius;
    Vec2d worldSize = getApp().getEnvSize();
    double world_width  = worldSize.x();
    double world_height = worldSize.y();

public :
    Collider (Vec2d position, double arg_radius); // constructeur
    Collider& operator= (Collider const&) = default; // opérateur =
    Collider (Collider const& other); // constructeur de copie

    Vec2d clamp (const Vec2d& vec);
    Vec2d directionTo (const Vec2d& to) const;
    Vec2d directionTo (const Collider& to) const;
    double distanceTo (const Vec2d& to) const;
    double distanceTo (const Collider& to) const;
    void move (const Vec2d& dx);
    void operator+= (const Vec2d& position2);

    bool isColliderInside (const Collider& other);
    bool isColliding (const Collider& other);
    bool isPointInside (const Vec2d& point);

    bool operator> (const Collider& body2);
    bool operator| (const Collider& body2);
    bool operator> (const Vec2d& point);

    Vec2d getPosition () const;
    double getRadius () const;
};
