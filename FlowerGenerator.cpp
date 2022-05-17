#include <iostream>
#include "FlowerGenerator.hpp"
#include <Random/Random.hpp>
#include "Application.hpp"
#include "Utility/Utility.hpp"

void FlowerGenerator::update(sf::Time dt) {         // calcule l'évolution des instances
    if (getAppConfig().active_flower_generator) {
        counter += dt;
        if ((counter > sf::seconds(getAppConfig().flower_generator_delay)) and (getAppConfig().active_flower_generator == true)) {
            counter = sf::Time::Zero;
            sf::Vector2i p (uniform(Vec2d(0,0), getApp().getEnvSize()));
            getAppEnv().addFlowerAt(p);
        }
    }

}

void FlowerGenerator::reset() {         // remet le compteur à zéro
    counter = sf::Time::Zero;
}
