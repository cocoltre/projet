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
    Vec2d centre;
    double rayon;
    Vec2d worldSize = getApp().getEnvSize();
    double world_width  = worldSize.x(); // largeur
    double world_height = worldSize.y(); // hauteur

public :
    Collider (Vec2d position, double arg_rayon);
    Vec2d clamp (const Vec2d& vec);
    Vec2d directionTo ( Vec2d to) ;
    Vec2d directionTo ( Collider to) ;
    double distanceTo ( Vec2d to) ;
    double distanceTo ( Collider to) ;
    void move (const Vec2d& dx);
    bool isColliderInside (Collider other);
    bool isColliding (Collider other);
    bool isPointInside (Vec2d point);
    bool operator> (Collider body2);
    bool operator| (Collider body2);
    bool operator> (Vec2d point);
    void operator+= (Vec2d position2);

    Collider& operator= (Collider const&) = default;
    Collider (Collider const& autre);

    Vec2d getPosition () const;
    double getRadius () const;
};

std::ostream& operator<< (std::ostream& sortie, Collider const& body);
