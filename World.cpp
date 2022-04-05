#include <iostream>
#include "World.hpp"
#include "Application.hpp"
#include "Utility/Vertex.hpp"
#include <vector>

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

        std::cout << file << std::endl;

        entree.close();
    }

    reloadCacheStructure();
    updateCache();
}

