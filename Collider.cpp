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

Collider::Collider(Vec2d position, double arg_rayon) : rayon(arg_rayon) {
    centre = clamp(position.x(),position.y());
}

Vec2d Collider::clamp (double x, double y) {

    x = fmod(x, world_width);
    if (x<0) {
        x += world_width;
    }

    y = fmod(y, world_height);
    if (y<0) {
        y += world_height;
    }
    return Vec2d (x,y);
}

Vec2d Collider::directionTo (Vec2d to) {
    Vec2d to2 (to.x(), to.y()+world_height);
    Vec2d to3 (to.x(), to.y()-world_height);
    Vec2d to4 (to.x()+world_width, to.y());
    Vec2d to5 (to.x()-world_width, to.y());
    Vec2d to6 (to.x()+world_width, to.y()+world_height);
    Vec2d to7 (to.x()+world_width, to.y()-world_height);
    Vec2d to8 (to.x()-world_width, to.y()+world_height);
    Vec2d to9 (to.x()-world_width, to.y()-world_height);

    std::array < Vec2d, 9 > L ({
    clamp(to2.x(), to2.y()),
    clamp(to3.x(), to3.y()),
    clamp(to4.x(), to4.y()),
    clamp(to5.x(), to5.y()),
    clamp(to6.x(), to6.y()),
    clamp(to7.x(), to7.y()),
    clamp(to8.x(), to8.y()),
    clamp(to9.x(), to9.y()),
    });

    double smallest_dist (distance(centre, to));
    Vec2d bon_vec(to);
    for (int i(1); i<9; ++i) {
        if (distance(centre, L[i]) < smallest_dist) {
            smallest_dist = distance(centre,L[i]);
            bon_vec = L[i];
        }
    }

    return Vec2d((bon_vec.x() - centre.x()), bon_vec.y() - centre.y());

}

Vec2d Collider::directionTo (Collider collider_to) {
    return directionTo (collider_to.centre);

}

double Collider::distanceTo (Vec2d to) {
    return directionTo(to).length();
}

double Collider::distanceTo (Collider collider_to) {
    return directionTo(collider_to).length();
}

Vec2d Collider::move (Vec2d dx) {
    return clamp(centre.x() + dx.x() , centre.y() + dx.y());
}

bool Collider::isColliderInside (Collider other) {
    if ((other.rayon >= rayon) and (distanceTo(other) <= other.rayon - rayon)) {
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
