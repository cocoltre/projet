#include <iostream>
#include "Flower.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Random/Random.hpp>

// CONSTRUCTOR AND DESTRUCTOR
Flower::Flower (Vec2d position, double arg_diam, double arg_pollen) : Collider(position, arg_diam/2), pollen(arg_pollen),
    indice(uniform(0, int(getValueConfig()["simulation"]["flower"]["textures"].size() -1))) {}  // constructor


// RELATIVE TO POLLEN
double Flower::takePollen(double amount) {          // take a certain amount of pollen to this Flower and return the amount that could have been taken
    if (amount < pollen) {
        pollen -= amount;
        return amount;
    }
    else {
        int pollen_init (pollen);
        pollen = 0.00;
        return pollen_init;
    }
}


// RELATIVE TO EVOLUTION
void Flower::drawOn(sf::RenderTarget& target) const {               // draw a Flower
    auto const& texture = getAppTexture(getValueConfig()["simulation"]["flower"]["textures"][indice].toString());
    auto flowerSprite = buildSprite(getPosition(), getRadius()*2, texture);
    target.draw(flowerSprite);

}

void Flower::update(sf::Time dt) {                                  // update the Flower's evolution
    double seuil (getAppConfig().flower_growth_threshold);
    double humidity = getAppEnv().find_humidity(getPosition());
    if (humidity >= seuil) {                                        // 1st step
        pollen += dt.asSeconds() * log(humidity/seuil);
    }

    double qt_seuil (getAppConfig().flower_growth_split);
    double dist (0.00);

    if (pollen > qt_seuil) {                                        // 2nd step
        Vec2d pp (getPosition());
        int i(0);
        do {
            dist = uniform(1.5*getRadius(), 2.5*getRadius());
            pp = getPosition() + Vec2d::fromRandomAngle() * dist;
            ++i;
        }
        while (getAppEnv().addFlowerAt(pp) == false and i < 100);
        pollen /=2;
    }   
}


// GETTER
double Flower::get_pollen() {                   // get this Flower's pollen's amount
    return pollen;
}






