#include <iostream>
#include "World.hpp"

class Env {
private :
    World world;

public :
    Env (); // constructeur par défaut
    void update(sf::Time dt);
    void drawOn(sf::RenderTarget& target);
    void reset();
    void loadWorldFromFile();
    float getSize () const;
    void resetControls();
};
