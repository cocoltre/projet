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

    struct Seed {
        sf::Vector2i position;
        Kind seed;
    };
    std::vector<Seed> seeds_;
    int nb_waterSeeds;
    int nb_grassSeeds;

public :
    void drawOn (sf::RenderTarget& target);
    void reloadConfig ();
    void reloadCacheStructure ();
    void updateCache ();
    void reset (bool regenerate = true);
    float getSize () const;

    void loadFromFile ();
    void step ();
    void seed_position (sf::Vector2i& a);
    void steps (int nb, bool b = false);
    void smooth ();
    void smooths (int n, bool b = false);
    void saveToFile();

};
