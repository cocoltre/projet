#include <iostream>
#include "Flower.hpp"
#include "Application.hpp"
#include "Utility/Utility.hpp"
#include <Random/Random.hpp>

Flower::Flower (Vec2d position, double arg_diam, double arg_pollen) : Collider(position, arg_diam/2), pollen(arg_pollen),
    indice(uniform(0, int(getValueConfig()["simulation"]["flower"]["textures"].size() -1))) {} // constructeur

double Flower::takePollen(double amount) {       // prélève une quantité donnée de pollen et retourne la quantité qui a pu être prélevée
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

void Flower::drawOn(sf::RenderTarget& target) const {                           // dessine une fleur   
    auto const& texture = getAppTexture(getValueConfig()["simulation"]["flower"]["textures"][indice].toString());
    auto flowerSprite = buildSprite(getPosition(), getRadius()*2, texture);
    target.draw(flowerSprite);

}

void Flower::update(sf::Time dt) {                                  // calcule l'évolution de la fleur
    double seuil (getAppConfig().flower_growth_threshold);
    double humidity = getAppEnv().find_humidity(getPosition());
    if (humidity >= seuil) {                                        // 1er pas
        pollen += dt.asSeconds() * log(humidity/seuil);
    }

    double qt_seuil (getAppConfig().flower_growth_split);
    double dist (0.00);

    if (pollen > qt_seuil) {                                        // 2e pas
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

double Flower::get_pollen() {                   // retourne le pollen de la fleur
    return pollen;
}






