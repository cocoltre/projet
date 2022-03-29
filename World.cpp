#include <iostream>
#include "World.hpp"
#include "Application.hpp"
#include "Utility/Vertex.hpp"
#include <vector>

float World::getSize() const {
    return cell_size;
}

void World::drawOn (sf::RenderTarget& target) {}


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
    renderingCache_.clear();
    sf::RenderStates rs;
    rs.texture = &getAppTexture(getAppConfig().rock_texture); // texture liée à la roche
    renderingCache_.draw(rockVertexes_.data(), rockVertexes_.size(), sf::Quads, rs);
    renderingCache_.display();
}

void World::reset (bool regenerate) {
    reloadConfig();
    reloadCacheStructure();
    updateCache();
}

