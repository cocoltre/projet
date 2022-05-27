#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Utility/Vec2d.hpp>
#include "Interface/Drawable.hpp"
#pragma once

enum class Kind : short { Grass, Water, Rock }; // 3 possible texture


class World {
private :

    // ATTRIBUTES

    int nbcells_;                               // this World's number of cells
    float cell_size;                            // the size of each cell
    std::vector<Kind> cells_;                   // this World's collection of cells
    sf::RenderTexture renderingCache_;          // to visualize the texture
    std::vector<sf::Vertex> grassVertexes_;     // the collection of index of grass cells
    std::vector<sf::Vertex> waterVertexes_;     // the collection of index of water cells
    std::vector<sf::Vertex> rockVertexes_;      // the collection of index of rock cells
    std::vector<sf::Vertex> humidityVertexes_;  // the collection of index of humid cells

    struct Seed {                               // structure of a Seed
        sf::Vector2i position;                  // the Seed's position
        Kind seed;                              // the type of Seed
    };
    std::vector<Seed> seeds_;                   // the World's collection of seeds
    int nb_waterSeeds;                          // the number of water Seeds
    int nb_grassSeeds;                          // the number of grass Seeds

    std::vector<double> humid_cells ;           // the collection of humidity levels
    int humidityRange_;                         // the humidity range

    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

    // PRIVATE METHODS

    // GETTER
    /*!
     * \brief create a collection of all the indexes inside a specific rectangle
     * \param topLeft the top left corner of the rectangle
     * \param bottomRight the bottom right corner of the rectangle
     * \return a collection of all the indexes inside a specific rectangle
     */
    std::vector<std::size_t> indexesForRect(sf::Vector2i const& topLeft, sf::Vector2i const& bottomRight) const;


    // RELATIVE TO EVOLUTION
    /*!
     * \brief reload the World's configuration, give values to the attributes (except vertexes)
     */
    void reloadConfig();

    /*!
     * \brief reload the World's Cache Structure, initialize the attributes (vertextes) related to the structure
     */
    void reloadCacheStructure();


    // RELATIVE TO MOVEMENT
    /*!
     * \brief randomly moves each Seed once
     */
    void step ();

    /*!
     * \brief randomly modifies the position of a Seed according to close moves
     * \param a the initial position of the Seed
     */
    void seed_position (sf::Vector2i& a);

    /*!
     * \brief smooth the different areas once
     */
    void smooth ();


    // TEST
    /*!
     * \brief check if a position is out the World
     * \param x the x of the position
     * \param y the y of the position
     * \return true if the position is out the World
     */
    bool IsOut(int x, int y);


    // RELATIVE TO COORDINATES
    /*!
     * \brief readjust the coordinates of a vector in the toric world
     * \param vec the vector
     * \return the coordinates of the vector in the toric world
     */
    Vec2d clamp (const Vec2d& vec);


    // RELATIVE TO HUMIDITY
    /*!
     * \brief initialize humidity levels
     */
    void set_humidity () ;


public :

    // DESTRUCTOR

    ~World () {} // destructor


    // GETTERS
    /*!
     * \brief get this World's full size, meaning the total number of cells
     * \return the total number of cells
     */
    int get_full_size() const;

    /*!
     * \brief get this World's width's size
     * \return this World's width's size
     */
    float getSize () const;

    /*!
     * \brief get this World's collection of humidity levels
     * \return this World's collection of humidity levels
     */
    std::vector<double> get_humid_cells() const;

    /*!
     * \brief get this World's number of cells
     * \return this World's number of cells
     */
    int get_nbcells_() const ;

    /*!
     * \brief get this World's collection of cells
     * \return this World's collection of cells
     */
    std::vector<Kind> get_cells_() const ;

    /*!
     * \brief get this World's cell size
     * \return this World's cell size
     */
    float get_cell_size() const ;



    // RELATIVE TO EVOLUTION
    /*!
     * \brief draw the World
     * \param target the environment where to draw
     */
    void drawOn (sf::RenderTarget& target) const ;

    /*!
     * \brief update the cache
     */
    void updateCache ();

    /*!
     * \brief reset the World
     * \param regenerate true so that the World evolves to an advanced stage
     */
    void reset (bool regenerate = true);


    // RELATIVE TO FILE MANAGEMENT
    /*!
     * \brief load a World from a file
     */
    void loadFromFile ();

    /*!
     * \brief save the World to a file
     */
    void saveToFile ();


    // RELATIVE TO MOVEMENT
    /*!
     * \brief randomly moves each Seed multiple times
     * \param nb the number of times
     * \param b true for updating the cache
     */
    void steps (int nb, bool b = false);

    /*!
     * \brief smooth the different areas several times
     * \param n the number of times
     * \param b true for updating the cache
     */
    void smooths (int n, bool b = false);


    // TESTS
    /*!
     * \brief check if a position is made of grass (meaning that flowers can grow there)
     * \param p the specific position
     * \return true if the position is made of grass
     */
    bool isGrowable(const Vec2d& p) const;

    /*!
     * \brief check if a position is not made of rock (meaning that bees can fly there)
     * \param p the specific position
     * \return true if the position is not made of rock
     */
    bool IsFlyable(Vec2d const& p) const;

    /*!
     * \brief check if an area from a position is entirely made of grass (meaning that Hives can grow there)
     * \param position the specific position
     * \param radius the radius of the area
     * \return true if the area from the position is entirely made of grass
     */
    bool isHiveable(const Vec2d& position, double radius) ;


   // RELATIVE TO COORDINATES
    /*!
     * \brief give the coordinates of the cell containing a specific position
     * \param p the specific position
     * \return the coordinates of the cell containing the specific position
     */
    Vec2d coord (const Vec2d& p) const;

    /*!
     * \brief get the index of the cell from a vector
     * \param x x coordinate of the vector
     * \param y y coordinate of the vector
     * \return the index of the cell from a vector
     */
    int index_cell (double x, double y) const;


};

