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
    Vec2d clamp (double x, double y);
    Vec2d directionTo (Vec2d to);
    Vec2d directionTo (Collider collider_to);
    double distanceTo (Vec2d to);
    double distanceTo (Collider collider_to);
    Vec2d move (Vec2d dx);
    bool isColliderInside (Collider other);
    bool isColliding (Collider other);
    bool isPointInside (Vec2d point);
    bool operator> (Collider body2);
    bool operator| (Collider body2);
    bool operator> (Vec2d point);

};

