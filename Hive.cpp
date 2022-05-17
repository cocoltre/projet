#include <iostream>
#include "Hive.hpp"
#include "Bee.hpp"
#include "Application.hpp"
#include "Config.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Vec2d.hpp"
#include "Random/Random.hpp"
#include "WorkerBee.hpp"
#include "ScoutBee.hpp"

Hive::Hive (Vec2d position, double arg_radius) : Collider(position, arg_radius),
    pollen(getAppConfig().hive_initial_nectar) {}; // constructeur


Bee* Hive::addBee(double scoutProb) {                                   // peuple la ruche
    Vec2d newposition (getPosition() + Vec2d::fromRandomAngle()*uniform(0.00, getRadius()));
    if (bernoulli(scoutProb) == true) {
        Bees.push_back(new ScoutBee(*this, newposition));
    }
    else {
        Bees.push_back(new WorkerBee(*this, newposition));
    }
    return Bees.back();

}

void Hive::update(sf::Time dt) {                        // fait évoluer toutes les abeilles de la ruche à chaque pas de temps dt
    std::vector<Bee*> vec;
    for (size_t i(0); i < Bees.size(); ++i) {
        Bees[i]->update(dt);
        if (Bees[i]->get_energy() == 0.00) {
            delete Bees[i];
            Bees[i] = nullptr;
        }
        else if (Bees[i]->getState() == WorkerBee::get_in_hive() or Bees[i]->getState() == ScoutBee::get_in_hive()) {
            vec.push_back(Bees[i]);

        }
    }
    Bees.erase(std::remove(Bees.begin(), Bees.end(), nullptr), Bees.end());

    if (vec.size() >= 2) {
        for (size_t i(0); i < vec.size()-1; ++i) {
            for (size_t j(i+1); j < vec.size(); ++j)
            vec[i]->interact(vec[j]);
        }
    }


    if (pollen >= getAppConfig().hive_reproduction_nectar_threshold and (int)Bees.size() < getAppConfig().hive_reproduction_max_bees) {
        addBee(getAppConfig().hive_reproduction_scout_proba);
    }

}

void Hive::drawOn(sf::RenderTarget& targetWindow) const {     // dessine la ruche
    auto const& texture = getAppTexture(getAppConfig().hive_texture);
    auto flowerSprite = buildSprite(getPosition(), getRadius()*2.5, texture);
    targetWindow.draw(flowerSprite);

    for (size_t i(0); i < Bees.size(); ++i) {               // pour afficher les abeilles
       Bees[i]->drawOn(targetWindow);
    }

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
        pollen -= qte;
        return qte;
    }
    else {
        int pollen_init (pollen);
        pollen = 0.00;
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

