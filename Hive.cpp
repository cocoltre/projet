#include <iostream>
#include "Hive.hpp"
#include "Application.hpp"
#include "Config.hpp"
#include "Utility/Utility.hpp"

Hive::Hive (Vec2d position, double arg_radius) : Collider(position, arg_radius),
    pollen(getAppConfig().hive_initial_nectar) {}; // constructeur


void Hive::addBee() {                                   // peuple la ruche

}

void Hive::update(sf::Time dt) {                        // fait évoluer toutes les abeilles de la ruche à chaque pas de temps dt

}

void Hive::drawOn(sf::RenderTarget& targetWindow) const {     // dessine la ruche
    auto const& texture = getAppTexture(getAppConfig().hive_texture);
    auto flowerSprite = buildSprite(getPosition(), getRadius()*2.5, texture);
    targetWindow.draw(flowerSprite);

    int text_size (30);                                     // pour l'affichage de la quantité de nectar
    sf::Color text_color(sf::Color::Red);
    Vec2d text_position (getPosition().x(), getPosition().y());

    if (isDebugOn() == true) {                          // pour afficher la quantité de nectar
        auto const text = buildText(to_nice_string(pollen), text_position, getAppFont(), text_size, text_color);
        targetWindow.draw(text);

    }
}

void Hive::dropPollen(double qte) {                     // augmente de qte la quantité de nectar de la ruche
    pollen += qte;
}

double Hive::takeNectar(double qte) {                     // prélève une quantité qte de nectar de la ruche
    if (qte < pollen) {
        this->pollen -= qte;
        return qte;
    }
    else {
        int pollen_init (pollen);
        this->pollen = 0.00;
        return pollen_init;
    }
}

void Hive::delete_bees () {
    if (Bees.size() != 0) {
        for (size_t i(0); i < Bees.size(); ++i) {
            delete Bees[i];
            Bees[i] = nullptr;
        }
        Bees.erase(std::remove(Bees.begin(), Bees.end(), nullptr), Bees.end());
    }
}
