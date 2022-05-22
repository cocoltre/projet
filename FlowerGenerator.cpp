#include <iostream>
#include "FlowerGenerator.hpp"
#include <Random/Random.hpp>
#include "Application.hpp"
#include "Utility/Utility.hpp"

// RELATIVE TO EVOLUTION
void FlowerGenerator::update(sf::Time dt) {         // update the counter and the generator of flowers
    if (getAppConfig().active_flower_generator) {
        counter += dt;
        if ((counter > sf::seconds(getAppConfig().flower_generator_delay)) and (getAppConfig().active_flower_generator == true)) {
            counter = sf::Time::Zero;
            sf::Vector2i p (uniform(Vec2d(0,0), getApp().getEnvSize()));
            getAppEnv().addFlowerAt(p);
        }
    }
}

void FlowerGenerator::reset() {                     // reset the counter
    counter = sf::Time::Zero;
}
