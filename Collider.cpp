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

Collider::Collider(Vec2d centre, double arg_rayon) : rayon(arg_rayon) {
    centre = clamp(centre);
}

Collider::Collider (Collider const& autre) : centre(autre.centre), rayon(autre.rayon) {}

Vec2d Collider::clamp (const Vec2d& vec) {
    double x (0.00);
    double y (0.00);

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

 Vec2d Collider::directionTo (Vec2d to)  {
    Vec2d to2 (to.x(), to.y()+world_height);
    Vec2d to3 (to.x(), to.y()-world_height);
    Vec2d to4 (to.x()+world_width, to.y());
    Vec2d to5 (to.x()-world_width, to.y());
    Vec2d to6 (to.x()+world_width, to.y()+world_height);
    Vec2d to7 (to.x()+world_width, to.y()-world_height);
    Vec2d to8 (to.x()-world_width, to.y()+world_height);
    Vec2d to9 (to.x()-world_width, to.y()-world_height);

    std::array < Vec2d, 9 > L ({to,to2,to3,to4,to5,to6,to7,to8,to9});

    double smallest_dist (distance(centre, to));
    Vec2d bon_vec(to);
    for (int i(1); i<9; ++i) {
        if (distance(centre, L[i]) < smallest_dist) {
            smallest_dist = distance(centre, L[i]);
            bon_vec = L[i];
        }
    }

    return (bon_vec - centre);

}

Vec2d Collider::directionTo (Collider to)  {
    return directionTo(to.centre);

}

double Collider::distanceTo (Vec2d to)  {
    return directionTo(to).length();
}

double Collider::distanceTo (Collider to)  {
    return directionTo(to).length();
}

void Collider::move (const Vec2d& dx) {
    this->centre = clamp(this->centre + dx);
}

void Collider::operator+= (Vec2d position2) {
    move(position2);
}

bool Collider::isColliderInside (Collider other) {
    if ((rayon >= other.rayon) and (distanceTo(other) <= rayon - other.rayon)) {
        return true;
    }
    else return false;
}

bool Collider::isColliding (Collider other) {
    if (distanceTo(other) <= other.rayon + rayon) {
        return true;
    }
    else return false;
}

bool Collider::isPointInside (Vec2d point) {
    if (distanceTo(point) <= rayon) {
        return true;
    }
    else return false;
}

bool Collider::operator> (Collider body2) {
    return (isColliderInside(body2));
}

bool Collider::operator| (Collider body2) {
    return (isColliding(body2));
}

bool Collider::operator> (Vec2d point) {
    return (isPointInside(point));
}

Vec2d Collider::getPosition() const {
    return this->centre;
}

double Collider::getRadius() const {
    return rayon;
}

std::ostream& operator<< (std::ostream& sortie, Collider const& body) {
    sortie << " Collider : position = " << body.getPosition() << " radius = " << body.getRadius() ;
    return sortie;
}
