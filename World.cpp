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

float World::getSize() const { // renvoie la taille du monde
    return cell_size * nbcells_ ;
}

void World::drawOn (sf::RenderTarget& target) const {             // affiche les cellules texturées et leur taux d'humidité
    int text_size (30);                                     // pour le taux d'humidité
    sf::Color text_color(sf::Color::Red);
    Vec2d cursor (getApp().getCursorPositionInView());
    Vec2d cursor_position (coord(cursor));
    Vec2d text_position (cursor.x() - 50, cursor.y() + 50);

    if (getAppConfig().showHumidity() == true) {            // pour afficher le taux d'humidité
        target.draw(humidityVertexes_.data(), humidityVertexes_.size(), sf::Quads);
        if (isDebugOn() == true) {                          // pour afficher les valeurs des taux d'humidité
            auto const text = buildText(to_nice_string(humid_cells[cursor_position.x() + cursor_position.y() * nbcells_]), text_position, getAppFont(), text_size, text_color);
            target.draw(text);
        }
    }
    else {                                                  // affiche la texture des cellules
    sf::Sprite cache(renderingCache_.getTexture());
    target.draw(cache);
    }
}


void World::reloadConfig () {                                   // donne des valeurs aux attributs (sauf vertexes)
    nbcells_ = getAppConfig().world_cells;
    cell_size = getAppConfig().world_size / nbcells_;
    std::vector<Kind> vec (nbcells_*nbcells_, Kind::Rock);
    cells_ = vec;

    const double eta (getAppConfig().world_humidity_init_level);    // déclaration et initialisation de constantes
    const double lambda (getAppConfig().world_humidity_decay_rate);
    const double seuil (getAppConfig().world_humidity_threshold);

    int hr(0);                                           // calcule le rayon d'humidité
    while (eta * exp(-hr/lambda) > seuil) {
        ++ hr;
    }
    humidityRange_ = hr;

    std::vector<double> vec2 (nbcells_*nbcells_);
    humid_cells = vec2;

    nb_waterSeeds = getAppConfig().world_nb_water_seeds;                    // compte le nombre de graines d'eau
    nb_grassSeeds = getAppConfig().world_nb_grass_seeds;                    // compte le nombre de graines d'herbe
    seeds_ = std::vector<Seed> (nb_waterSeeds + nb_grassSeeds);       // donne la bonne taille à l'ensemble seeds_

}

void World::reloadCacheStructure () {                           // initialise les attributs (vertexes) liés à la texture et humidité des cellules
    grassVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    waterVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    rockVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    humidityVertexes_ = generateVertexes(getValueConfig()["simulation"]["world"]["textures"], nbcells_, cell_size);
    renderingCache_.create(nbcells_ * cell_size, nbcells_ * cell_size);     // initialise la texture du terrain
}

void World::updateCache () {                                    // met à jour l'attribut renderingCache_ (crée la texture)
    double minHumidity (humid_cells[0]);                        // calcule l'humidité minimale et maximale du terrain
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
            id = x + y*nbcells_;
            index = indexesForCellVertexes(x, y, nbcells_ );    // vector des quatre indexes (N-S-E-O) des cellules vertexes

            if (cells_[id] == Kind::Grass) {                    // rend la cellule d'herbe verte
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 255;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[id] == Kind::Water) {                    // rend la cellule d'eau bleue
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 255;
                    rockVertexes_[index[j]].color.a = 0;
                }
            }
            if (cells_[id] == Kind::Rock) {                     // rend la cellule de roche beige
                for (int j(0); j < 4; ++j) {
                    grassVertexes_[index[j]].color.a = 0;
                    waterVertexes_[index[j]].color.a = 0;
                    rockVertexes_[index[j]].color.a = 255;
                }
            }


            blue_level = (humid_cells[id] - minHumidity)/ (maxHumidity - minHumidity) * 255; // calcule le niveau de bleu de la cellule selon son taux d'humidité
            for (int j(0); j < 4; ++j) {
                humidityVertexes_[index[j]].color = sf::Color(0, 0, blue_level); // rend la cellule plus ou moins bleue selon son taux d'humidité
            }
        }
    }

    sf::RenderStates rs;
    rs.texture = &getAppTexture(getAppConfig().rock_texture); // texture liée à la rohe
    renderingCache_.draw(rockVertexes_.data(), rockVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().water_texture); // texture liée à l'eau
    renderingCache_.draw(waterVertexes_.data(), waterVertexes_.size(), sf::Quads, rs);

    rs.texture = &getAppTexture(getAppConfig().grass_texture); // texture liée à l'herbe
    renderingCache_.draw(grassVertexes_.data(), grassVertexes_.size(), sf::Quads, rs);

    renderingCache_.display();                                 // rend effectif le dessin de la texture



}

void World::reset (bool regenerate) {                          // initialise l'ensemble des attributs du monde
    reloadConfig();                                            // initialise les attributs (sauf vertexes)
    reloadCacheStructure();                                    // initialise les attributs (vertexes) liés à la texture et à l'humidité

    for (int w(0); w < nb_waterSeeds; ++w) {                   // initialise seeds_ en y mettant le nb de graines d'eau voulu à des positions aléatoires
        seeds_[w].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[w].seed = Kind::Water;
        cells_[seeds_[w].position.x + seeds_[w].position.y * nbcells_] = Kind::Water; // transmission des graines aux cellules
    }

    for (size_t g(nb_waterSeeds); g < seeds_.size(); ++g) {     // même chose pour les graines d'herbe
        seeds_[g].position = sf::Vector2i (uniform(0, nbcells_-1), uniform(0, nbcells_-1));
        seeds_[g].seed = Kind::Grass;
        if (cells_[seeds_[g].position.x + seeds_[g].position.y * nbcells_] != Kind::Water) { // car les cellules d'eau ne peuvent être recouvertes
            cells_[seeds_[g].position.x + seeds_[g].position.y * nbcells_] = seeds_[g].seed;
            }
    }

    if (regenerate) {           // booléen faux pour les tests
        steps(getAppConfig().world_generation_steps);
        smooths(getAppConfig().world_generation_smoothness_level);
    }

    set_humidity();             // met à jour le taux d'humidité des cellules
    updateCache();              // dessine les textures

}


void World::loadFromFile () {                   // pour charger un monde depuis un fichier
    std::string file (getApp().getResPath() + getAppConfig().world_init_file);
    std::ifstream entree;
    entree.open (file.c_str());

    if (entree.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        std::string phrase;
        getline(entree, phrase);                // lit la 1ère ligne : le nombre de cellules par ligne
        nbcells_ = std::stoi(phrase);

        std::string phrase2;
        getline(entree, phrase2);               // lit la 2ème ligne : la taille des cellules
        cell_size = std::stoi(phrase2);

        std::string phrase3;                    // lit la 3ème ligne : la texture de chaque celluule
        getline(entree, phrase3);
        phrase3.erase(remove(phrase3.begin(),phrase3.end(),' '),phrase3.end()); // supprime les espaces
        std::vector<Kind> vec (nbcells_*nbcells_);
        for (int i(0); i< nbcells_*nbcells_; ++i) {
            vec[i] = static_cast<Kind>(std::stoi(std::string(1, phrase3[i]))) ;
        }
        cells_ = vec;

        std::string phrase4;
        std::string phrase_cut("");
        getline(entree, phrase4);               // lit la 4ème ligne : le taux d'humidité de chaque cellule
        std::vector<double> vec2 (nbcells_*nbcells_);
        for (int i(0); i< nbcells_*nbcells_; ++i) {         // supprime les espaces
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

    reloadCacheStructure();         // met à jour les attributs
    updateCache();
}

void World::step () {               // fait se déplacer 1 fois chaque graine de manière aléatoire
    for (size_t i(0); i < seeds_.size(); ++i) {
        if (seeds_[i].seed == Kind::Grass) {    // déplace une graine d'herbe
            seed_position(seeds_[i].position);
        }
        else {                                  // déplace une graine d'eau
            if (bernoulli(getAppConfig().water_seeds_teleport_proba) == 0) {
                seed_position(seeds_[i].position);                  // déplacement proche
            }
            else {                                                  // déplacement aléatoire dans tout le terrain
                int nx(0);
                int ny(0);

                do {
                nx = uniform(0, nbcells_ - 1);
                ny = uniform(0, nbcells_ - 1);
                } while (seeds_[i].position.x == nx and seeds_[i].position.y == ny); // pour forcer la graine à se déplacer

                seeds_[i].position.x = nx;
                seeds_[i].position.y = ny;
            }
        }
        cells_[seeds_[i].position.x + seeds_[i].position.y * nbcells_] = seeds_[i].seed; // mise à jour de la texture de la cellule

    }

    set_humidity(); // met à jour le taux d'humidité des cellules
}

void World::seed_position (sf::Vector2i& a) { // modifie aléatoirement la position d'une graine selon des déplacements proches
    int nx(0);
    int ny(0);

    do {
    nx = uniform(-1, 1);
    ny = uniform(-1, 1);
    } while (std::abs(nx - ny) != 1); // pour forcer un déplacement proche

    a.x += nx;
    a.y += ny;

    if (a.y > nbcells_ - 1) { // adapte la position au monde torique
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

void World::steps (int nb, bool b) { // fait se déplacer plusieurs fois chaque graine de manière aléatoire
    for (int i(0); i < nb; ++i) {
        step ();
    }

    if (b == true) {
        updateCache();
    }
}

void World::smooth () {             // lisse les différentes zones 1 fois
    auto copie_de_cells_ = cells_;  // algorithme lissant copie_de_cells ici
    double t (0.00);
    int index (1);

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = x + y * nbcells_;
            if ((copie_de_cells_[index] == Kind::Grass) or (copie_de_cells_[index] == Kind::Rock)) { // traitement si la cellule est une cellule d'herbe ou de roche et est entourée d'eau
                if (y == 0) {                                                                        // si la cellule se trouve sur la 1ère ligne (en haut) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Water) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Water;                                       // si la cellule est entourée d'eau, elle devient une cellule d'eau
                    }
                }

                else if (y == nbcells_ - 1) {                                                            // si la cellule se trouve sur la dernière ligne (en bas) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Water) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Water;
                    }
                }

                if (x == 0) {                                                                       // si la cellule se trouve sur la 1ère colonne (à gauche) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Water) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Water;
                    }
                }

                else if (x == nbcells_ - 1) {                                                            // si la cellule se trouve sur la dernière colonne (à droite) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Water) { ++t; }
                    if (t/5 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Water;
                    }
                }

                else if (x != 0 and x != nbcells_ - 1 and y != 0 and y != nbcells_ - 1) {                // pour l'intérieur du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Water) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Water) { ++t; }
                    if (t/6 > getAppConfig().smoothness_water_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Water;
                    }
                }
            }
        }
    }

    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            index = x + y * nbcells_;
            if (copie_de_cells_[index] == Kind::Rock) {                                     // puis, traitement si la cellule est une cellule de roche et est entourée d'herbe
                if (y == 0) {                                                               // si la cellule se trouve sur la 1ère ligne (en haut) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Grass;                               // si la cellule de roche est entourée d'herbe, elle devient une cellule d'herbe
                    }
                }

                else if (y == nbcells_ - 1) {                                                    // si la cellule se trouve sur la dernière ligne (en bas) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Grass;
                    }
                }

                if (x == 0) {                                                               // si la cellule se trouve sur la 1ère colonne (à gauche) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Grass;
                    }
                }

                else if (x == nbcells_ - 1) {                                                    // si la cellule se trouve sur la dernière colonne (à droite) du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (t/5 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Grass;
                    }
                }

                else if (x != 0 and x != nbcells_ - 1 and y != 0 and y != nbcells_ - 1) {       // pour l'intérieur du terrain
                    t = 0.00;
                    if (copie_de_cells_[index - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index - nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ - 1] == Kind::Grass) { ++t; }
                    if (copie_de_cells_[index + nbcells_ + 1] == Kind::Grass) { ++t; }
                    if (t/8 > getAppConfig().smoothness_grass_neighbor_ratio) {
                        copie_de_cells_[index] = Kind::Grass;
                    }
                }
            }
        }
    }

    std::swap(cells_, copie_de_cells_); // quand le lissage est fini on copie copie_de_cells_ dans cell_ (le swap est une optimisation)
    set_humidity();                     // met à jour le taux d'humidité de chaque cellule
}

void World::smooths (int n, bool b) { // lisse les différentes zones plusieurs fois
    for (int i(0); i < n; ++i) {
        smooth ();
    }

    if (b == true) {
        updateCache();
    }
}

void World::saveToFile () {           // sauvegarde une nouvelle configuration dans un fichier
    std::ofstream fichier;
    fichier.open(getApp().getResPath() + "new_world.map");

    if (fichier.fail()) {
        throw std::runtime_error("le fichier n'existe pas.");
    }
    else {
        fichier << nbcells_ << std::endl;
        fichier << cell_size << std::endl;

        for (size_t i(0); i < cells_.size(); ++i) {
            if (cells_[i] == Kind::Grass ) {            // écrit '0' si la cellule est d'herbe
                fichier << '0' << ' ';
            }
            else if (cells_[i] == Kind::Water ) {       // écrit '1' si la cellule est d'eau
                fichier << '1' << ' ';
            }
            else {                                      // écrit '2' si la cellule est de roche
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

void World::set_humidity () {       // initialise le taux d'humidité de chaque cellule du terrain
    const double eta (getAppConfig().world_humidity_init_level);    // déclaration et initialisation de constantes
    const double lambda (getAppConfig().world_humidity_decay_rate);

    double dist (0.00);
    humid_cells.clear();            // remet à zéro le taux d'humidité de chaque cellule
    for (int x(0); x < nbcells_; ++x) {
        for (int y(0); y < nbcells_; ++y) {
            if (cells_[x + y*nbcells_] == Kind::Water) {                                                // si la cellule est d'eau
                for (int nx(x - humidityRange_); nx < x + humidityRange_ + 2; ++ nx) {      // alors pour toutes les cellules de son voisinage
                    for (int ny(y - humidityRange_); ny < y + humidityRange_ + 2; ++ ny) {
                        dist = std::hypot(x-nx, y-ny);                                                  // on calcule la distance les séparant,
                        humid_cells[nx + ny*nbcells_] += eta*exp(-dist/lambda);                   // puis le taux d'humité de la cellule change
                    }
                }
            }
        }
    }
}

bool World::isGrowable(const Vec2d& p) {                    // détermine si une cellule est d'herbe
    return (cells_[p.x() + p.y()*nbcells_] == Kind::Grass);
}

Vec2d World::coord (const Vec2d& p) const {                       // retourne les coordonnées de la cellule contenant la position p
    return Vec2d(int(p.x()/cell_size), int(p.y()/cell_size));
}

std::vector<double> World::get_humid_cells() {              // retourne le vector d'humidité des cellules
    return humid_cells;
}

int World::get_nbcells_() {                                 // retourne le nombre de cellules par ligne du monde
    return nbcells_;
}

std::vector<Kind> World::get_cells_() {                     // retourne cells_
    return cells_;
}

float World::get_cell_size() {
    return cell_size;
}


bool World::isHiveable(const Vec2d& position, double radius) {                        // détermine si une ruche peut être ajoutée (si le sol est d'herbe)
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

Vec2d World::clamp (const Vec2d& vec) { // réajuste les coordonnées d'un vecteur dans le monde torique
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

std::vector<std::size_t> World::indexesForRect(sf::Vector2i const& topLeft, sf::Vector2i const& bottomRight) const {  // renvoie les indices des cellules du terrain
                                                                                                                      // que la ruche englobe
    std::vector<std::size_t> vec;
    // Handle toric world coordinates for rectangles:
        //
        // case 1) if topLeft and bottomRight are really what they should be,
        //         then the rectangle is not wrapped around the toric world.
    if ((topLeft.x < bottomRight.x) and (topLeft.y < bottomRight.y)) {
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
    }

    // case 3) if the left and right sides are swapped,
    //         then the rectangle is wrapped on the right side of the world.
    else if ((topLeft.x > bottomRight.x) and (topLeft.y < bottomRight.y)) {
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // côté droit
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
        for (int i(0); i <= bottomRight.x; ++i) {                               // côté gauche
            for (int j(topLeft.y); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
    }

    // case 2) if topLeft and bottomRight are swapped,
    //         then bottomRight was actually outside.
    else if ((topLeft.x > bottomRight.x) and (topLeft.y > bottomRight.y)) {
        for (int i(0); i <= bottomRight.x; ++i) {                               // en haut à gauche
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // en haut à droite
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
        for (int i(0); i <= bottomRight.x; ++i) {                               // en bas à gauche
            for (int j(topLeft.y); j < nbcells_; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
        for (int i(topLeft.x); i < nbcells_; ++i) {                             // en bas à droite
            for (int j(topLeft.y); j < nbcells_; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
    }
        // case 4) if the top and bottom sides are swapped,
        //         then the rectangle is swapped on the bottom side of the world.
        //
    else if ((topLeft.x < bottomRight.x) and (topLeft.y > bottomRight.y)) {
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {                       // en haut
            for (int j(0); j <= bottomRight.y; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
        for (int i(topLeft.x); i <= bottomRight.x; ++i) {                       // en bas
            for (int j(topLeft.y); j <= nbcells_; ++j) {
                vec.push_back(i+j*nbcells_);
            }
        }
    }
    return vec;

        // Graphically, where `*` is topLeft and `%` is bottomRight
        // and `o` and `x` are the area covered by the rectangle:
        //
        //       case 1                case 3
        //    +---------+           +---------+
        //    |         |           |         |
        //    | *--+    |        *--|-+    *--|
        //    | |xx|    |        |oo|x|    |xx|
        //    | +--%    |        +--|-%    +--|
        //    |         |           |         |
        //    +---------+           +---------+
        //
        // *----+
        // |oo o|case 2                case 4
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

bool World::IsFlyable(Vec2d const& p) {
    return (cells_[coord(p).x() + coord(p).y()*nbcells_] != Kind::Rock);
}
