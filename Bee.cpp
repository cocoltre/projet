#include "Bee.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>

Bee::Bee(Hive& Home, const Vec2d& position, const double& arg_rad, const double& energy, const double& ScalSpeed)  // constructeur
    :Collider(position, arg_rad*2),
      Home(Home),
      speed(Vec2d::fromRandomAngle()*ScalSpeed),
      energy(energy),
      texture (getAppTexture(getConfig()["texture"].toString()))
{}


bool Bee::Isdead () {                   // retourne true si l'abeille est morte
    if (energy == 0.00) {
        return true;
    }
    else return false;
}

j::Value const& Bee::getConfig() {              // retourne de façon polymorphique les propriétés spécifiques à chaque sous-type d'abeille
    return getValueConfig()["simulation"]["bees"]["scout"];
}

void Bee::drawOn(sf::RenderTarget& target) const {                           // dessine une abeille

    auto BeeSprite = buildSprite(getPosition(), getRadius(), texture);
    double α (speed.angle());

    if ((α >= PI / 2) or (α <= -PI/2)) {
        BeeSprite.scale(1, -1);
    }
    BeeSprite.rotate(α /DEG_TO_RAD);
    target.draw(BeeSprite);
}

void Bee::update(sf::Time dt) {                 // simule l'évolution d'une abeille
    move(dt);
    if (energy - 0.1 * dt.asSeconds() >= 0.00) {
        energy -= 0.1 * dt.asSeconds();
    }
    else { energy = 0.00; }
}


void Bee::move(sf:: Time dt) {              // déplace l'abeille
    if (bernoulli(getConfig()["moving behaviour"]["random"]["rotation probability"].toDouble()) == true) {
        double alphamax (getConfig()["moving behaviour"]["random"]["rotation angle max"].toDouble()) ;
        double alpha (uniform(-alphamax, alphamax));
        speed.rotate(alpha);
    }

    Vec2d possible_position (getPosition() + speed * dt.asSeconds());
    if (getAppEnv().IsFlyable(possible_position)) {
        Collider::move(speed * dt.asSeconds());
    }
    else {
        double beta (0.00);
        if (bernoulli(0.5) == true) {
            beta = PI / 4;
        }
        else {
            beta = - PI / 4;
        }

        speed.rotate(beta);
    }
}

double Bee::get_energy() {              // retourne le niveau d'énergie
    return energy;
}
