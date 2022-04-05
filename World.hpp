#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

enum class Kind : short { Herbe, Eau, Roche };

class World {
private :
    int nbcells_;
    float cell_size;
    std::vector<Kind> cells_;
    sf::RenderTexture renderingCache_;
    std::vector<sf::Vertex> grassVertexes_;
    std::vector<sf::Vertex> waterVertexes_;
    std::vector<sf::Vertex> rockVertexes_;

public :
    void reloadConfig ();
    void drawOn (sf::RenderTarget& target);
    void reloadCacheStructure ();
    void updateCache ();
    void reset (bool regenerate = true);
    float getSize () const;

    void loadFromFile ();
};

