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

// CONSTRUCTORS AND DESTRUCTORS
Hive::Hive (Vec2d position, double arg_radius) : Collider(position, arg_radius),
    pollen(getAppConfig().hive_initial_nectar) {};      // constructor

void Hive::delete_bees () {                             // delete all the Bees
    if (Bees.size() != 0) {
        for (size_t i(0); i < Bees.size(); ++i) {
            delete Bees[i];
            Bees[i] = nullptr;
        }
        Bees.erase(std::remove(Bees.begin(), Bees.end(), nullptr), Bees.end());
    }
}


// RELATIVE TO EVOLUTION
void Hive::update(sf::Time dt) {                        // update the Hive's evolution
    std::vector<Bee*> vec;                              // vector of the Bees that are IN the Hive
    for (size_t i(0); i < Bees.size(); ++i) {           // update the Bees' evolution
        Bees[i]->update(dt);
        if (Bees[i]->Isdead()) {                        // delete the dead Bees
            delete Bees[i];
            Bees[i] = nullptr;
        }
        else if (Bees[i]->getState() == WorkerBee::get_in_hive() or Bees[i]->getState() == ScoutBee::get_in_hive()) {
            vec.push_back(Bees[i]);
        }
    }
    Bees.erase(std::remove(Bees.begin(), Bees.end(), nullptr), Bees.end());

    if (vec.size() >= 2) {                              // interactions between all the Bees in the hive
        for (size_t i(0); i < vec.size()-1; ++i) {
            for (size_t j(i+1); j < vec.size(); ++j)
            vec[i]->interact(vec[j]);
        }
    }

    if (pollen >= getAppConfig().hive_reproduction_nectar_threshold and (int)Bees.size() < getAppConfig().hive_reproduction_max_bees) {     // add Bees while it is possible
        addBee(getAppConfig().hive_reproduction_scout_proba);
    }
}

void Hive::drawOn(sf::RenderTarget& targetWindow) const {           // draw the Hive
    auto const& texture = getAppTexture(getAppConfig().hive_texture);
    auto flowerSprite = buildSprite(getPosition(), getRadius()*2.5, texture);
    targetWindow.draw(flowerSprite);

    for (size_t i(0); i < Bees.size(); ++i) {                       // draw the Bees
       Bees[i]->drawOn(targetWindow);
    }

    int text_size (30);                                             // indicate the nectar's amount
    sf::Color text_color(sf::Color::Red);
    Vec2d text_position (getPosition().x(), getPosition().y());

    if (isDebugOn() == true) {                                      // debugging option
        auto const text = buildText(to_nice_string(pollen), text_position, getAppFont(), text_size, text_color);
        targetWindow.draw(text);
    }
}


// RELATIVE TO POLLEN/NECTAR
void Hive::dropPollen(double qte) {                                 // drop a certain amount of nectar in the Hive
    pollen += qte;
}

double Hive::takeNectar(double qte) {                               // take a certain amount of nectar of the Hive
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


// RELATIVE TO BEES
Bee* Hive::addBee(double scoutProb) {                               // add a Bee to this Hive
    Vec2d newposition (getPosition() + Vec2d::fromRandomAngle()*uniform(0.00, getRadius()));
    if (bernoulli(scoutProb) == true) {
        Bees.push_back(new ScoutBee(*this, newposition));
    }
    else {
        Bees.push_back(new WorkerBee(*this, newposition));
    }
    return Bees.back();

}
