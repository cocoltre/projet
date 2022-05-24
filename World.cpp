#include <iostream>
#include "World.hpp"
#include "Application.hpp"
#include "Utility/Vertex.hpp"
#include <vector>
#include <Random/Random.hpp>
#include "Utility/Utility.hpp"
#include <iomanip>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>


// GETTERS
int World::get_full_size() const {
    return nbcells_ * nbcells_ ;
}

float World::getSize() const {                                      // get this World's width's size
    return cell_size * nbcells_ ;
}

std::vector<double> World::get_humid_cells() const {                // get this World's collection of humidity levels
    return humid_cells;
}

int World::get_nbcells_() const {                                   // get this World's number of cells
    return nbcells_;
}

std::vector<Kind> World::get_cells_() const {                       // get this World's collection of cells
    return cells_;
}

float World::get_cell_size() const {                                // get this World's cell size
    return cell_size;
}

std::vector<std::size_t> World::indexesForRect(sf::Vector2i const& topLeft, sf::Vector2i const& bottomRight) const {  // return the indexes of the cells of the area
                                                                                                                      // that the Hive encompasses
    std::vector<std::size_t> vec;

    // Handle toric world coordinates for rectangles:
        //
        // case 1) if topLeft and bottomRight are really what they should be,
        //         then the rectangle is not wrapped around the toric world.

    if ((topLeft.x < bottomRight.x) and (topLeft.y < bottomRight.y)) {
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
    }

    // case 2) if the left and right sides are swapped,
    //         then the rectangle is wrapped on the right side of the world.

    else if ((topLeft.x > bottomRight.x) and (topLeft.y < bottomRight.y)) {
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // right side
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
        for (int i(0); i <= bottomRight.x; ++i) {                               // left side
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
    }

    // case 3) if topLeft and bottomRight are swapped,
    //         then bottomRight was actually outside.

    else if ((topLeft.x > bottomRight.x) and (topLeft.y > bottomRight.y)) {
        for (int i(0); i <= bottomRight.x; ++i) {                               // on the top corner left
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // on the top corner right
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
        for (int i(0); i <= bottomRight.x; ++i) {                               // on the bottom corner left
            for (int j(topLeft.y); j < nbcells_; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // on the bottom corner right
            for (int j(topLeft.y); j < nbcells_; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
    }

        // case 4) if the top and bottom sides are swapped,
        //         then the rectangle is swapped on the bottom side of the world.

    else if ((topLeft.x < bottomRight.x) and (topLeft.y > bottomRight.y)) {
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {                       // top side
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {                       // bottom side
            for (int j(topLeft.y); j <= nbcells_; ++j) {
                vec.push_back(index_cell(i,j));
            }
        }
    }

    return vec;

        // Graphically, where `*` is topLeft and `%` is bottomRight
        // and `o` and `x` are the area covered by the rectangle:
        //
        //       case 1                case 2
        //    +---------+           +---------+
        //    |         |           |         |
        //    | *--+    |        *--|-+    *--|
        //    | |xx|    |        |oo|x|    |xx|
        //    | +--%    |        +--|-%    +--|
        //    |         |           |         |
        //    +---------+           +---------+
        //
        // *----+
        // |oo o|case 3                case 4
        // |  +---------+           +---------+
        // |oo|x|    |xx|           |   |xx|  |
        // +--|-%    +--|           |   +--%  |
        //    |         |           |         |
        //    |-+    *--|           |   *--+  |
        //    |x|    |xx|           |   |xx|  |
        //    +---------+           +---------+
        //                              |oo|
        //                              +--%
        // Remembering the axes:
        //
        //   +---> x
        //   |
        //   |
        //   Ë…
        //   y
        //
}


// RELATIVE TO EVOLUTION
void World::drawOn (sf::RenderTarget& target) const {               // draw the World
    int text_size (30);                                             // for humidity levels
    sf::Color text_color(sf::Color::Red);
    Vec2d cursor (getApp().getCursorPositionInView());
    Vec2d cursor_position (coord(cursor));
    Vec2d text_position (cursor.x() - 50, cursor.y() + 50);

    if (getAppConfig().showHumidity() == true) {                    // to show humidity levels
        target.draw(humidityVertexes_.data(), humidityVertexes_.size(), sf::Quads);
        if (isDebugOn() == true) {                                  // to show the values of the humidity levels
            auto const text = buildText(to_nice_string(humid_cells[index_cell(cursor_position.x(), cursor_position.y())]), text_position, getAppFont(), text_size, text_color);
            target.draw(text);
        }
    }
    else {                                                          // to show cells' textures
    sf::Sprite cache(renderingCache_.getTexture());
    target.draw(cache);
    }
}

void World::reloadConfig () {                                       // give values to attributes (except vertexes)
    nbcells_ = getAppConfig().world_cells;
    cell_size = getAppConfig().world_size / nbcells_;
    cells_ = std::vector<Kind> (get_full_size(), Kind::Rock);

    const double eta (getAppConfig().world_humidity_init_level);    // declaration and initialization of constants
    const double lambda (getAppConfig().world_humidity_decay_rate);
    const double seuil (getAppConfig().world_humidity_threshold);

    humidityRange_ = 0;
    while (eta * exp(-humidityRange_/lambda) > seuil) {                         // calculate humidity range
        ++ humidityRange_;
    }

    humid_cells = std::vector<double> (get_full_size());

    nb_waterSeeds = getAppConfig().world_nb_water_seeds;                    // count the number of water Seeds
    nb_grassSeeds = getAppConfig().world_nb_grass_seeds;                    // count the number of grass Seeds
    seeds_ = std::vector<Seed> (nb_waterSeeds + nb_grassSeeds);             // give the correct size to the collection of Seeds


}

void World::reloadCacheStructure () {                                       // initialize the attributes (vertexes) related to the texture and humidity of the cells
    std::vector<sf::Vertex> generate_vertexes (generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size));
    grassVertexes_ = generate_vertexes;
    waterVertexes_ = generate_vertexes;
    rockVertexes_ = generate_vertexes;
    humidityVertexes_ = generate_vertexes;
    renderingCache_.create(nbcells_ * cell_size, nbcells_ * cell_size);     // initialize the terrain texture

}

void World::updateCache () {                                                // update renderingCache_ attribute (create texture)
    renderingCache_.clear();

    double minHumidity (humid_cells[0]);                                    // calculate the minimum and maximum humidity of the ground
    double maxHumidity (humid_cells[0]);
    for (size_t i(1); i < humid_cells.size(); ++i) {
        if (humid_cells[i] < minHumidity) {
            minHumidity = humid_cells[i];
        }
        else if (humid_cells[i] > maxHumidity) {
            maxHumidity = humid_cells[i];
        }
    }

    int id(0);
    std::vector<std::size_t> index (4);
    double blue_level (0.00);
    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            id = index_cell(x,y);
            index = indexesForCellVertexes(x, y, nbcells_ );                // vector of the four indexes (N-S-E-O) of the vertex cells

            if (cells_[id] == Kind::Grass) {                                // make grass cell green
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 255;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[id] == Kind::Water) {                                // make water cell blue
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 255;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[id] == Kind::Rock) {                                 // make rock cell beige
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 255;
                }
            }


            blue_level = (humid_cells[id] - minHumidity)/ (maxHumidity - minHumidity) * 255; // calculate the blue level of the cell according to its humidity level
            for (int j(0); j < 4; ++j) {
                humidityVertexes_[index[j]].color = sf::Color(0, 0, blue_level);            // make the cell more or less blue depending on its humidity level
            }
        }
    }

    sf::RenderStates rs;
    rs.texture = &getAppTexture(getAppConfig().rock_texture);                               // rock bound texture
    renderingCache_.draw(rockVertexes_.data(), rockVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().water_texture);                              // water bound texture
    renderingCache_.draw(waterVertexes_.data(), waterVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().grass_texture);                              // grass bound texture
    renderingCache_.draw(grassVertexes_.data(), grassVertexes_.size(), sf::Quads, rs);

    renderingCache_.display();                                                              // implement the drawing of the texture

}

void World::reset (bool regenerate) {                                                       // initialize the set of world attributes
    reloadConfig();                                                                         // initialize attributes (except vertexes)
    reloadCacheStructure();                                                                 // initialize attributes (vertexes) related to texture and humidity

    int ind(0);

    for (int w(0); w < nb_waterSeeds; ++w) {                            // initialize seeds by putting the desired number of water Seeds in random positions
        seeds_[w].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[w].seed = Kind::Water;
        ind = index_cell(seeds_[w].position.x, seeds_[w].position.y);
        cells_[ind] = Kind::Water;       // transmission of Seeds to cells
    }

    for (size_t g(nb_waterSeeds); g < seeds_.size(); ++g) {                                 // same for grass Seeds
        seeds_[g].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[g].seed = Kind::Grass;
        ind = index_cell(seeds_[g].position.x, seeds_[g].position.y);
        if (cells_[ind] != Kind::Water) {    // because water cells cannot be covered
            cells_[ind] = seeds_[g].seed;
        }
    }

    if (regenerate) {           // false boolean for tests
        steps(getAppConfig().world_generation_steps);
        smooths(getAppConfig().world_generation_smoothness_level);

    }

    set_humidity();             // updates cells' humidity
    updateCache();              // draw the textures
}


// RELATIVE TO FILE MANAGEMENT
void World::loadFromFile () {                                                       // load a World from a file
    std::string file (getApp().getResPath() + getAppConfig().world_init_file);
    std::ifstream entree;
    entree.open (file.c_str());

    if (entree.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        std::string phrase;
        getline(entree, phrase);                            // read the 1st line: the number of cells per line
        nbcells_ = std::stoi(phrase);

        std::string phrase2;
        getline(entree, phrase2);                           // read the 2nd line: the size of the cells
        cell_size = std::stoi(phrase2);

        std::string phrase3;                                // reads the 3rd line: the texture of each cell
        getline(entree, phrase3);
        phrase3.erase(remove(phrase3.begin(),phrase3.end(),' '),phrase3.end());     // delete spaces
        int full_size (get_full_size());
        std::vector<Kind> vec (full_size);
        for (int i(0); i< full_size; ++i) {
            vec[i] = static_cast<Kind>(std::stoi(std::string(1, phrase3[i]))) ;
        }
        cells_ = vec;

        std::string phrase4;
        std::string phrase_cut("");
        getline(entree, phrase4);                           // read the 4th line: the humidity level of each cell
        std::vector<double> vec2 (full_size);
        for (int i(0); i< full_size; ++i) {         // delete spaces
            while (phrase4[0] != ' ') {
                phrase_cut += phrase4[0];
                phrase4.erase(0,1);
            }
            if (phrase4[0] == ' ') {
                phrase4.erase(0,1);
            }
            vec2[i] = std::stod(phrase_cut);
            phrase_cut.clear();
        }
        humid_cells = vec2;

        std::cout << file << " " << std::endl;

        entree.close();
    }

    reloadCacheStructure();                 // update attributes
    updateCache();
}

void World::saveToFile () {                 // save the World to a file
    std::ofstream fichier;
    fichier.open(getApp().getResPath() + "new_world.map");

    if (fichier.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        fichier << nbcells_ << std::endl;
        fichier << cell_size << std::endl;

        for (size_t i(0); i < cells_.size(); ++i) {
            if (cells_[i] == Kind::Grass ) {            // write '0' if the cell is grass
                fichier << '0' << ' ';
            }
            else if (cells_[i] == Kind::Water ) {       // write '1' if the cell is water
                fichier << '1' << ' ';
            }
            else {                                      // write '2' if the cell is rock
                fichier << '2' << ' ';
            }
        }
        fichier << std::endl;

        for (size_t i(0); i < cells_.size(); ++i) {
            fichier << humid_cells[i] << ' ';
        }

        fichier.close();
        std::cout << "map saved to new_world.map" << std::endl;
    }
}


// RELATIVE TO MOVEMENT
void World::step () {                               // randomly moves each Seed once
    for (size_t i(0); i < seeds_.size(); ++i) {
        if (seeds_[i].seed == Kind::Grass) {        // move a grass Seed
            seed_position(seeds_[i].position);
        }
        else {                                      // move a water Seed
            if (bernoulli(getAppConfig().water_seeds_teleport_proba) == 0) {
                seed_position(seeds_[i].position);                  // close move
            }
            else {                                                  // random movement throughout the terrain
                int nx(0);
                int ny(0);
                int i(0);

                do {
                nx = uniform(0, nbcells_ - 1);
                ny = uniform(0, nbcells_ - 1);
                ++i;
                } while (seeds_[i].position.x == nx and seeds_[i].position.y == ny and i < 100);    // to force the Seed to move until 100 unsuccessful tests

                seeds_[i].position.x = nx;
                seeds_[i].position.y = ny;
            }
        }
        cells_[index_cell(seeds_[i].position.x, seeds_[i].position.y)] = seeds_[i].seed; // update cell texture
    }

    set_humidity();                                 // update cells' humidity
}

void World::seed_position (sf::Vector2i& a) {       // randomly modifies the position of a Seed according to close moves
    int nx(0);
    int ny(0);

    do {
    nx = uniform(-1, 1);
    ny = uniform(-1, 1);
    } while (std::abs(nx - ny) != 1);   // to force a close move

    a.x += nx;
    a.y += ny;

    if (a.y > nbcells_ - 1) {           // adapt the position to the toric world
        a.y = nbcells_ - 1;
    }
    else if (a.y < 0) {
        a.y = nbcells_;
    }
    else if (a.x > nbcells_ - 1) {
        a.x = nbcells_ - 1;
    }
    else if (a.x < 0) {
        a.x = nbcells_;
    }
}

void World::steps (int nb, bool b) {        // randomly move each Seed multiple times
    for (int i(0); i < nb; ++i) {
        step ();
    }

    if (b == true) {
        updateCache();
    }
}

void World::smooth () {                     // smooth the different areas once
    auto copie_de_cells_ = cells_;          // algorithm that smooths copy_of_cells here
    double t (0.00);
    int index (1);

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = index_cell(x,y);
            if ((cells_[index] == Kind::Grass) or (cells_[index] == Kind::Rock)) { // treatment if the cell is a grass or rock cell, and is surrounded by water
                t = 0.00;
                for (int i(x-1); i <= x+1; ++i) {                                                    // form a square around the cell
                    for (int j(y-1); j <= y+1; ++j) {
                        if (not IsOut(i,j)) {                                                        // if the coordinates of the square's cells are in the World
                            if (cells_[index_cell(i, j)] == Kind::Water) { ++t; }
                        }
                    }
                }
                if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                    copie_de_cells_[index] = Kind::Water;                                       // if the cell is surrounded by water, it becomes a water cell
                }
            }
        }
    }

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = index_cell(x,y);
            if (cells_[index] == Kind::Rock) {                                     // then, treatment if the cell is a rock cell and is surrounded by grass
                t = 0.00;
                for (int i(x-1); i <= x+1; ++i) {                                                    // form a square around the cell
                    for (int j(y-1); j <= y+1; ++j) {
                        if (not IsOut(i,j)) {                                                        // if the coordinates of the square's cells are in the World
                            if (cells_[index_cell(i, j)] == Kind::Grass) { ++t; }
                        }
                    }
                }
                if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                    copie_de_cells_[index] = Kind::Grass;                                       // if the cell is surrounded by grass, it becomes a grass cell
                }
            }
        }
    }

    std::swap(cells_, copie_de_cells_);         // when the smoothing is finished, we copy copy_of_cells_ in cell_ (the swap is an optimization)
    set_humidity();                             // update the humidity level of each cell
}

void World::smooths (int n, bool b) {           // smooth the different areas several times
    for (int i(0); i < n; ++i) {
        smooth ();
    }

    if (b == true) {
        updateCache();
    }
}


// TESTS
bool World::isGrowable(const Vec2d& p) const {                                    // determine if a cell is grass
    return (cells_[index_cell(p.x(),p.y())] == Kind::Grass);
}

bool World::IsFlyable(Vec2d const& p) const {                                     // check if a position is not made of rock (meaning that bees can fly there)
    return (cells_[index_cell(coord(p).x(),coord(p).y())] != Kind::Rock);
}

bool World::isHiveable(const Vec2d& position, double radius) {                                  // determine if a Hive can be added (if the position is grass)
    sf::Vector2i topLeft (coord(clamp({position.x() - radius, position.y() - radius})));
    sf::Vector2i bottomRight (coord(clamp({position.x() + radius, position.y() + radius})));
    std::vector<std::size_t> indexes(indexesForRect(topLeft, bottomRight));

    for (size_t i(0); i < indexes.size(); ++i) {
        if ((cells_[indexes[i]] == Kind::Water) or (cells_[indexes[i]] == Kind::Rock)) {
            return false;
        }
    }
    return true;
}

bool World::IsOut(int x, int y) {
    if ((x < 0) or (x >= nbcells_) or (y < 0) or (y >= nbcells_)) {
        return true;
    }
    else return false;
}


// RELATIVE TO COORDINATES
Vec2d World::coord (const Vec2d& p) const {                                 // give the coordinates of the cell containing a specific position
    return Vec2d(int(p.x()/cell_size), int(p.y()/cell_size));
}

Vec2d World::clamp (const Vec2d& vec) {                                     // readjust the coordinates of a vector in the toric world
    double x (0.00);
    double y (0.00);
    Vec2d worldSize = getApp().getEnvSize();
    double world_height = worldSize.y();
    double world_width  = worldSize.x();

    x = fmod(vec.x(), world_width);
    if (x<0) {
        x += world_width;
    }

    y = fmod(vec.y(), world_height);
    if (y<0) {
        y += world_height;
    }
    return {x,y};
}

int World::index_cell(double x, double y) const {
    return x + y * nbcells_;
}

// RELATIVE TO HUMIDITY
void World::set_humidity () {                                       // initialize the humidity rate of each cell in the field
    const double eta (getAppConfig().world_humidity_init_level);    // declaration and initialization of constants
    const double lambda (getAppConfig().world_humidity_decay_rate);

    double dist (0.00);
    humid_cells.clear();                                            // reset the humidity level of each cell

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            if (cells_[index_cell(x,y)] == Kind::Water) {                                                // if the cell is a water cell,
                for (int nx(x - humidityRange_); nx < x + humidityRange_ + 2; ++ nx) {                  // then for all cells in its neighborhood,
                    for (int ny(y - humidityRange_); ny < y + humidityRange_ + 2; ++ ny) {
                        dist = std::hypot(x-nx, y-ny);                                                  // we calculate the distance separating them,
                        humid_cells[index_cell(nx,ny)] += eta*exp(-dist/lambda);                         // then the humidity level of the cell changes
                    }
                }
            }
        }
    }
}

