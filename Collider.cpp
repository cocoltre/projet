/*
 * POOSV EPFL 2022
 * @authors:
 * Marco Antognini
 */

#include <Application.hpp>
#include <Env/Collider.hpp>
#include <cmath> // abs and fmod
#include <algorithm>
#include <array>

// OPERATORS AND DESTRUCTOR
Collider::Collider (Vec2d center, double arg_radius) : radius(arg_radius) {     // constructor
    this->center = clamp(center);
}

Collider::Collider (Collider const& other) : center(other.center), radius(other.radius) {}  // copy's constructor


// MOVEMENT
Vec2d Collider::clamp (const Vec2d& vec) {                      // readjust the vector's coordonnates in the toric world
    double x (0.00);
    double y (0.00);
    Vec2d worldSize = getApp().getEnvSize();
    double world_height = worldSize.y();
    double world_width  = worldSize.x();

    x = fmod(vec.x(), world_width);
    if (x<0) {
        x += world_width;
    }

    y = fmod(vec.y(), world_height);
    if (y<0) {
        y += world_height;
    }
    return {x,y};
}

Vec2d Collider::directionTo (const Vec2d& to) const {           // find the shortest way in the toric world to go to a specific place
    Vec2d worldSize = getApp().getEnvSize();
    double world_height = worldSize.y();
    double world_width  = worldSize.x();

    Vec2d to2 (to.x(), to.y()+world_height);                    // the 9 moving possibilities
    Vec2d to3 (to.x(), to.y()-world_height);
    Vec2d to4 (to.x()+world_width, to.y());
    Vec2d to5 (to.x()-world_width, to.y());
    Vec2d to6 (to.x()+world_width, to.y()+world_height);
    Vec2d to7 (to.x()+world_width, to.y()-world_height);
    Vec2d to8 (to.x()-world_width, to.y()+world_height);
    Vec2d to9 (to.x()-world_width, to.y()-world_height);

    std::array < Vec2d, 9 > L ({to,to2,to3,to4,to5,to6,to7,to8,to9});

    double smallest_dist (distance(center, to));                // calculate the shortest vector to go to the specific place
    Vec2d good_vec(to);
    for (int i(1); i<9; ++i) {
        if (distance(center, L[i]) < smallest_dist) {
            smallest_dist = distance(center, L[i]);
            good_vec = L[i];
        }
    }

    return (good_vec - center);

}

Vec2d Collider::directionTo (const Collider& to) const {        // find the shortest way in the toric world to go to the position of a specific Collider from this Collider
    return directionTo(to.center);

}

double Collider::distanceTo (const Vec2d& to) const {           // calculate the distance of this Collider to a specific place
    return directionTo(to).length();
}

double Collider::distanceTo (const Collider& to) const {        // calculate the distance of this Collider to the position of a specific Collider
    return directionTo(to).length();
}

void Collider::move (const Vec2d& dx) {                         // move the center of this Collider from a vector in the toric world
    center = clamp(center + dx);
}

void Collider::operator+= (const Vec2d& position2) {            // create an operator that moves the center of this Collider from a vector in the toric world
    move(position2);
}


// TESTS
bool Collider::isColliderInside (const Collider& other) const { // check if a Collider is inside this Collider
    if ((radius >= other.radius) and (distanceTo(other) <= radius - other.radius)) {
        return true;
    }
    else return false;
}

bool Collider::isColliding (const Collider& other) const {  // check if a Collider is colliding with this Collider
    return (distanceTo(other) <= other.radius + radius) ;
}

bool Collider::isPointInside (const Vec2d& point) const {   // check if a point is inside this Collider
    return (distanceTo(point) <= radius) ;
}

bool Collider::operator> (const Collider& body2) const {    // create an operator that checks if a Collider is inside this Collider
    return (isColliderInside(body2));
}

bool Collider::operator| (const Collider& body2) const {    // create an operator that checks if a Collider is colliding with this Collider
    return (isColliding(body2));
}

bool Collider::operator> (const Vec2d& point) const {       // create an operator that checks if a point is inside this Collider
    return (isPointInside(point));
}


// GETTERS
Vec2d Collider::getPosition() const {                       // get this Collider's position
    return center;
}

double Collider::getRadius() const {                        // get this Collider's radius
    return radius;
}

// extern operator that shows a Collider's information (center's position and radius)
std::ostream& operator<< (std::ostream& sortie, Collider const& body) {
    sortie << " Collider : position = " << body.getPosition() << " radius = " << body.getRadius() ;
    return sortie;
}
