#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include "Interface/Drawable.hpp"
#pragma once

enum class Kind : short { Grass, Water, Rock }; // 3 textures possibles


class World {
private :
    int nbcells_;
    float cell_size;
    std::vector<Kind> cells_;
    sf::RenderTexture renderingCache_;
    std::vector<sf::Vertex> grassVertexes_;
    std::vector<sf::Vertex> waterVertexes_;
    std::vector<sf::Vertex> rockVertexes_;
    std::vector<sf::Vertex> humidityVertexes_;

    struct Seed {
        sf::Vector2i position;
        Kind seed;
    };
    std::vector<Seed> seeds_;
    int nb_waterSeeds;
    int nb_grassSeeds;

    std::vector<double> humid_cells ;
    int humidityRange_;

public :
    ~World () {}; // destructeur
    float getSize () const;

    void drawOn (sf::RenderTarget& target) const ;
    void reloadConfig ();
    void reloadCacheStructure ();
    void updateCache ();
    void reset (bool regenerate = true);

    void loadFromFile ();
    void step ();
    void seed_position (sf::Vector2i& a);
    void steps (int nb, bool b = false);
    void smooth ();
    void smooths (int n, bool b = false);
    void saveToFile ();

    void set_humidity () ;

    bool isGrowable(const Vec2d& p);
    Vec2d coord (const Vec2d& p) const ;

    std::vector<double> get_humid_cells();
    int get_nbcells_();
    std::vector<Kind> get_cells_();
    float get_cell_size();

    bool isHiveable(const Vec2d& position, double radius);
    Vec2d clamp (const Vec2d& vec);
    std::vector<std::size_t> indexesForRect(sf::Vector2i const& topLeft, sf::Vector2i const& bottomRight) const;

    bool IsFlyable(Vec2d const& p);
};

