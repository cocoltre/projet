#include "Bee.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Utility/Vec2d.hpp>
#include <Random/Random.hpp>

// CONSTRUCTOR, DESTRUCTOR AND CONFIGURATION
Bee::Bee(Hive& Home, const Vec2d& position, double arg_rad, double energy2, double ScalSpeed, std::vector<state> const& possible_states)  // constructor
    : Collider(position, arg_rad*2),
      CFSM(possible_states),
      Home(Home),
      speed(Vec2d::fromRandomAngle()*ScalSpeed),
      energy(energy2),
      memory(0.00, 0.00),
      memory_value(false),
      mode("at rest"),
      target(position),
      avoidanceClock_(sf::Time::Zero)

{}


// MOVEMENT
void Bee::move(sf::Time dt) {                       // move the Bee during a small amount of time
    if (mode == "randomly") {
        randomMove(dt);
    }
    else if (mode == "targeted") {
        targetMove(dt);
    }
}

void Bee::targetMove(sf::Time dt) {                 // move the Bee in a precise direction during a small amount of time
    if (avoidanceClock_ <= sf::Time::Zero) {        // if the clock is to Zero or under
        speed = directionTo(target)/directionTo(target).length()*speed.length();
    }
    else {
        avoidanceClock_ -= dt;
    }

    Vec2d possible_position (getPosition() + speed * dt.asSeconds());
    if (getAppEnv().IsFlyable(possible_position)) {     // if the next position is not rock
        Collider::move(speed * dt.asSeconds());
    }
    else {                                              // if the next position is rock
        avoidanceClock_ = sf::seconds(getConfig()["moving behaviour"]["target"]["avoidance delay"].toInt());        // launching of the clock
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

void Bee::randomMove(sf:: Time dt) {                    // move the Bee in a random way during a small amount of time

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


// RELATIVE TO EVOLUTION
bool Bee::Isdead () const {       // check if the Bee is dead (when it has no energy)
    return (energy == 0.00);
}

void Bee::drawOn(sf::RenderTarget& target) const {              // draw a Bee
    auto BeeSprite = buildSprite(getPosition(), getRadius(), getAppTexture(getConfig()["texture"].toString()));
    double alpha (speed.angle());

    if ((alpha >= PI / 2) or (alpha <= -PI/2)) {
        BeeSprite.scale(1, -1);
    }
    BeeSprite.rotate(alpha /DEG_TO_RAD);
    target.draw(BeeSprite);

    if (isDebugOn() == true) {                                  // debugging option
        if (mode == "randomly") {
            auto shape = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5.0);
            target.draw(shape);
        }
        else if (mode == "targeted") {
            auto shape2 = buildAnnulus(getPosition(), getRadius(), sf::Color::Blue, 3.0);
            target.draw(shape2);
        }
    }
}

void Bee::update(sf::Time dt) {                                 // update the Bee's evolution
    action(dt);
    double rate (0.00);
    if (mode == "at rest") {
        rate = getConfig()["energy"]["consumption rates"]["idle"].toDouble();
    }
    else {
        move(dt);
        rate = getConfig()["energy"]["consumption rates"]["moving"].toDouble();
    }

    if (energy - rate * dt.asSeconds() >= 0.00) {   // update the Bee's energy
        energy -= rate * dt.asSeconds();
    }
    else { energy = 0.00; }
}


// GETTERS
double Bee::get_energy() const {                        // get the Bee's energy
    return energy;
}

bool Bee::get_value_memory() const {                    // get the Bee's memory's value
    return memory_value;
}

Vec2d Bee::get_memory() const {                         // get the Bee's memory
    return memory;
}

Vec2d Bee::home_position () const {                           // get the Bee's Hive's position
    return Home.getPosition();
}

double Bee::home_radius() const {                             // get the Bee's Hive's radius
    return Home.getRadius();
}


// CHANGERS
void Bee::change_mode(std::string newmode) {            // change the Bee's mode
    mode = newmode;
}

void Bee::change_target(Vec2d const& newtarget) {       // change the Bee's target
    target = newtarget;
}

void Bee::change_memory(Vec2d const& newmemory) {       // change the Bee's memory
    memory = newmemory;
}

void Bee::change_value_memory(bool b) {                 // change the Bee's memory's value
    memory_value = b;
}

void Bee::gain_energy(double qte) {                     // convert a certain amount of nectar into energy to the Bee
    energy += Home.takeNectar(qte);
}

void Bee::learnFlowerLocation(const Vec2d& flowerPosition) {        // learn a new Flower's Position
    memory = flowerPosition;
    memory_value = true;
}


// FOR STATS
void Bee::change_nb_scout(int a) {                      // change the number of ScoutBees
    getAppEnv().change_nb_scout(a);
}

void Bee::change_nb_worker(int b) {                     // change the number of WorkerBees
    getAppEnv().change_nb_worker(b);
}


// RELATIVE TO POLLEN
void Bee::dropPollen(double qte) {                      // drop a certain amount of pollen in the Bee's Hive
    Home.dropPollen(qte);
}




