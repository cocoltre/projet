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

Collider::Collider (Vec2d center, double arg_radius) : radius(arg_radius) { // constructeur
    this->center = clamp(center);
}

Collider::Collider (Collider const& other) : center(other.center), radius(other.radius) {} // constructeur de copie

Vec2d Collider::clamp (const Vec2d& vec) { // réajuste les coordonnées d'un vecteur dans le monde torique
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

 Vec2d Collider::directionTo (const Vec2d& to) const {      // calcule les coordonnées du vecteur de déplacement à partir d'un vecteur
    Vec2d to2 (to.x(), to.y()+world_height);                // les 9 possibilités de déplacement
    Vec2d to3 (to.x(), to.y()-world_height);
    Vec2d to4 (to.x()+world_width, to.y());
    Vec2d to5 (to.x()-world_width, to.y());
    Vec2d to6 (to.x()+world_width, to.y()+world_height);
    Vec2d to7 (to.x()+world_width, to.y()-world_height);
    Vec2d to8 (to.x()-world_width, to.y()+world_height);
    Vec2d to9 (to.x()-world_width, to.y()-world_height);

    std::array < Vec2d, 9 > L ({to,to2,to3,to4,to5,to6,to7,to8,to9});

    double smallest_dist (distance(center, to));            // calcule le vecteur qui nécessitera le plus petit déplacement
    Vec2d good_vec(to);
    for (int i(1); i<9; ++i) {
        if (distance(center, L[i]) < smallest_dist) {
            smallest_dist = distance(center, L[i]);
            good_vec = L[i];
        }
    }

    return (good_vec - center);

}

Vec2d Collider::directionTo (const Collider& to) const { // calcule les coordonnées du vecteur de déplacement à partir d'un Collider
    return directionTo(to.center);

}

double Collider::distanceTo (const Vec2d& to) const { // calcule la longueur du déplacement à partir d'un vecteur
    return directionTo(to).length();
}

double Collider::distanceTo (const Collider& to) const { // calcule la longueur du déplacement à partir d'un Collider
    return directionTo(to).length();
}

void Collider::move (const Vec2d& dx) {         // modifie la position du centre d'un Collider à partir d'un vecteur
    this->center = clamp(this->center + dx);    // réajuste ses coordonnées dans le monde torique
}

void Collider::operator+= (const Vec2d& position2) { // opérateur +=, fonction similaire à la méthode move
    move(position2);
}

bool Collider::isColliderInside (const Collider& other) { // détermine si un Collider est à l'intérieur d'un autre
    if ((radius >= other.radius) and (distanceTo(other) <= radius - other.radius)) {
        return true;
    }
    else return false;
}

bool Collider::isColliding (const Collider& other) { // détermine s'il y a collision entre deux Colliders
    if (distanceTo(other) <= other.radius + radius) {
        return true;
    }
    else return false;
}

bool Collider::isPointInside (const Vec2d& point) { // détermine si un point est à l'intérieur d'un Collider
    if (distanceTo(point) <= radius) {
        return true;
    }
    else return false;
}

bool Collider::operator> (const Collider& body2) { // détermine si un Collider est à l'intérieur d'un autre
    return (isColliderInside(body2));
}

bool Collider::operator| (const Collider& body2) { // détermine si deux Colliders sont en collision
    return (isColliding(body2));
}

bool Collider::operator> (const Vec2d& point) { // détermine si un point est à l'intérieur d'un Collider
    return (isPointInside(point));
}

Vec2d Collider::getPosition() const { // renvoie la position du centre d'un Collider
    return this->center;
}

double Collider::getRadius() const { // renvoie le rayon d'un Collider
    return radius;
}

std::ostream& operator<< (std::ostream& sortie, Collider const& body) { // opérateur externe, permet d'afficher la position du centre et le rayon d'un Collider
    sortie << " Collider : position = " << body.getPosition() << " radius = " << body.getRadius() ;
    return sortie;
}
