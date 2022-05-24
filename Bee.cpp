#include "Bee.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>

Bee::Bee(Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states)  // constructeur
    : Collider(position, arg_rad*2),
      CFSM(possible_states),
      Home(Home),
      speed(Vec2d::fromRandomAngle()*ScalSpeed),
      energy(energy2),
      memory(0.00, 0.00),
      memory_value(false),
      mode("au repos"),
      target(position),
      avoidanceClock_(sf::Time::Zero)

{}


bool Bee::Isdead () {                   // retourne true si l'abeille est morte
    if (energy == 0.00) {
        return true;
    }
    else return false;
}


void Bee::drawOn(sf::RenderTarget& target) const {                           // dessine une abeille
    auto BeeSprite = buildSprite(getPosition(), getRadius(), getAppTexture(getConfig()["texture"].toString()));
    double α (speed.angle());

    if ((α >= PI / 2) or (α <= -PI/2)) {
        BeeSprite.scale(1, -1);
    }
    BeeSprite.rotate(α /DEG_TO_RAD);
    target.draw(BeeSprite);

    if (isDebugOn() == true) {
        if (mode == "aléatoire") {
            auto shape = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5.0);
            target.draw(shape);
        }
        else if (mode == "ciblé") {
            auto shape2 = buildAnnulus(getPosition(), getRadius(), sf::Color::Blue, 3.0);
            target.draw(shape2);
        }
    }

}

void Bee::update(sf::Time dt) {                 // simule l'évolution d'une abeille
    action(dt);
    double rate (0.00);
    if (mode == "au repos") {
        rate = getConfig()["energy"]["consumption rates"]["idle"].toDouble();
    }
    else {
        move(dt);
        rate = getConfig()["energy"]["consumption rates"]["moving"].toDouble();
    }


    if (energy - rate * dt.asSeconds() >= 0.00) {
        energy -= rate * dt.asSeconds();
    }
    else { energy = 0.00; }
}

void Bee::move(sf::Time dt) {
    if (mode == "aléatoire") {
        randomMove(dt);
    }
    else if (mode == "ciblé") {
        targetMove(dt);
    }
}

void Bee::targetMove(sf::Time dt) {
    if (avoidanceClock_ <= sf::Time::Zero) {
        speed = directionTo(target)/directionTo(target).length()*speed.length();
    }
    else {
        avoidanceClock_ -= dt;
    }

    Vec2d possible_position (getPosition() + speed * dt.asSeconds());
    if (getAppEnv().IsFlyable(possible_position)) {
        Collider::move(speed * dt.asSeconds());
    }
    else {
        avoidanceClock_ = sf::seconds(getConfig()["moving behaviour"]["target"]["avoidance delay"].toInt());
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

void Bee::randomMove(sf:: Time dt) {              // déplace l'abeille

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

double Bee::get_energy() const {              // retourne le niveau d'énergie
    return energy;
}

void Bee::change_mode(std::string newmode) {
    mode = newmode;
}

void Bee::change_target(Vec2d const& newtarget) {
    target = newtarget;
}

void Bee::change_memory(Vec2d const& newmemory) {
    memory = newmemory;
}

void Bee::change_value_memory() {
    if (memory_value == false) { memory_value = true; }
    else { memory_value = false; }
}


bool Bee::get_value_memory() const {
    return memory_value;
}

Vec2d Bee::home_position () {
    return Home.getPosition();
}

double Bee::home_radius() {
    return Home.getRadius();
}


void Bee::gain_energy(double qte) {
    Home.takeNectar(qte);
    energy += qte;
}


