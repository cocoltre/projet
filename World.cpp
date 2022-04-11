#include <iostream>
#include "World.hpp"
#include "Application.hpp"
#include "Utility/Vertex.hpp"
#include <vector>
#include <Random/Random.hpp>

float World::getSize() const {
    return cell_size * nbcells_ ;
}

void World::drawOn (sf::RenderTarget& target) {
    sf::Sprite cache(renderingCache_.getTexture());
    target.draw(cache);
}


void World::reloadConfig () {
    this->nbcells_ = getAppConfig().world_cells;
    this->cell_size = getAppConfig().world_size / nbcells_;
    std::vector<Kind> vec (nbcells_*nbcells_, Kind::Roche);
    this->cells_ = vec;
}

void World::reloadCacheStructure () {
    grassVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    waterVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    rockVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    int horizontalSize(nbcells_ * cell_size);
    int verticalSize(nbcells_ * cell_size);
    renderingCache_.create(horizontalSize, verticalSize);

    nb_waterSeeds = getAppConfig().world_nb_water_seeds;
    nb_grassSeeds = getAppConfig().world_nb_grass_seeds;
    this->seeds_ = std::vector<Seed> (nb_waterSeeds + nb_grassSeeds);
}

void World::updateCache () {
    sf::RenderStates rs;
    int i(0);
    std::vector<std::size_t> index (4);

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            i = x + y*nbcells_;
            index = indexesForCellVertexes(x, y, nbcells_ );

            if (cells_[i] == Kind::Herbe) {
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 255;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[i] == Kind::Eau) {
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 255;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[i] == Kind::Roche) {
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 255;
                }
            }
        }
    }

    rs.texture = &getAppTexture(getAppConfig().rock_texture); // texture liée à la roche
    renderingCache_.draw(rockVertexes_.data(), rockVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().water_texture); // texture liée à l'eau
    renderingCache_.draw(waterVertexes_.data(), waterVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().grass_texture); // texture liée à l'herbe
    renderingCache_.draw(grassVertexes_.data(), grassVertexes_.size(), sf::Quads, rs);

    renderingCache_.display();
}

void World::reset (bool regenerate) {
    reloadConfig();
    reloadCacheStructure();

    for (int w(0); w < nb_waterSeeds; ++w) {
        seeds_[w].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[w].seed = Kind::Eau;
        cells_[seeds_[w].position.x + seeds_[w].position.y * nbcells_] = seeds_[w].seed;
    }

    for (size_t g(nb_waterSeeds); g < seeds_.size(); ++g) {
        seeds_[g].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[g].seed = Kind::Herbe;
        if (cells_[seeds_[g].position.x + seeds_[g].position.y * nbcells_] != Kind::Eau) {
            cells_[seeds_[g].position.x + seeds_[g].position.y * nbcells_] = seeds_[g].seed;
            }
    }

    if (regenerate) {
        steps(getAppConfig().world_generation_steps);
        smooths(getAppConfig().world_generation_smoothness_level);
    }

    updateCache();

}

//-----
#include <iomanip>
#include <fstream>
#include <string>


void World::loadFromFile () {
    std::string file (getApp().getResPath() + getAppConfig().world_init_file);
    std::ifstream entree (file.c_str());

    if (entree.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        std::string phrase;
        getline(entree, phrase);
        this->nbcells_ = std::stoi(phrase);

        std::string phrase2;
        getline(entree, phrase2);
        this->cell_size = std::stoi(phrase2);

        std::string phrase3;
        getline(entree, phrase3);
        phrase3.erase(remove(phrase3.begin(),phrase3.end(),' '),phrase3.end());
        std::vector<Kind> vec (nbcells_*nbcells_);
        for (int i(0); i< nbcells_*nbcells_; ++i) {
            vec[i] = static_cast<Kind>(std::stoi(std::string(1, phrase3[i]))) ;
        }
        this->cells_ = vec;

        std::cout << file << " " << std::endl;

        entree.close();
    }
    reloadCacheStructure();
    updateCache();
}

void World::step () {
    for (size_t i(0); i < seeds_.size(); ++i) {
        if (seeds_[i].seed == Kind::Herbe) {
            seed_position(seeds_[i].position);
        }
        else {
            if (bernoulli(getAppConfig().water_seeds_teleport_proba) == 0) {
                seed_position(seeds_[i].position);
            }
            else {
                int nx(0);
                int ny(0);

                do {
                nx = uniform(0, nbcells_ - 1);
                ny = uniform(0, nbcells_ - 1);
                } while (seeds_[i].position.x == nx and seeds_[i].position.y == ny);

                seeds_[i].position.x = nx;
                seeds_[i].position.y = ny;
            }
        }
        cells_[seeds_[i].position.x + seeds_[i].position.y * nbcells_] = seeds_[i].seed;
    }
}

void World::seed_position (sf::Vector2i& a) {
    int nx(0);
    int ny(0);

    do {
    nx = uniform(-1, 1);
    ny = uniform(-1, 1);
    } while (std::abs(nx - ny) != 1);

    a.x += nx;
    a.y += ny;

    if (a.y > nbcells_ - 1) {
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

void World::steps (int nb, bool b) {
    for (int i(0); i < nb; ++i) {
        step ();
    }

    if (b == true) {
        updateCache();
    }
}

void World::smooth () {
    auto copie_de_cells_ = cells_;  // algorithme lissant copie_de_cells ici
    double t (0.00);
    int index (1);

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = x + y * nbcells_;
            if ((copie_de_cells_[index] == Kind::Herbe) or (copie_de_cells_[index] == Kind::Roche)) {
                if (y == 0) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Eau;
                    }
                }

                if (x == 0) {
                    t = 0.00;
                    if (copie_de_cells_[index + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Eau;
                    }
                }

                if (y == nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Eau;
                    }
                }

                if (x == nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Eau;
                    }
                }

                if (x != 0 and x != nbcells_ - 1 and y != 0 and y != nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Eau) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Eau) { ++t; }
                    if (t/6 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Eau;
                    }
                }
            }
        }
    }

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = x + y * nbcells_;
            if (copie_de_cells_[index] == Kind::Roche) {
                if (y == 0) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Herbe;
                    }
                }

                if (y == nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Herbe;
                    }
                }

                if (x == 0) {
                    t = 0.00;
                    if (copie_de_cells_[index + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Herbe;
                    }
                }

                if (x == nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Herbe;
                    }
                }

                if (x != 0 and x != nbcells_ - 1 and y != 0 and y != nbcells_ - 1) {
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Herbe) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Herbe) { ++t; }
                    if (t/8 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Herbe;
                    }
                }
            }
        }
    }

    std::swap(cells_, copie_de_cells_); // quand le lissage est fini on copie copie_de_cells_ dans cell_ (le swap est une optimisation).

}

void World::smooths (int n, bool b) {
    for (int i(0); i < n; ++i) {
        smooth ();
    }

    if (b == true) {
        updateCache();
    }
}

void World::saveToFile() {
    std::ofstream fichier("new_world.map");

    if (fichier.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        fichier << nbcells_ << std::endl;
        fichier << cell_size << std::endl;

        for (size_t i(0); i < cells_.size(); ++i) {
            fichier << static_cast<short>(cells_[i]) << " ";
        }

        fichier.close();
    }
}
