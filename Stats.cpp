#include <iostream>
#include "Stats/Stats.hpp"
#include "Application.hpp"

// RELATIVE TO EVOLUTION
void Stats::drawOn(sf::RenderTarget& target) const {        // draw the Stats
    graphs.at(id)->drawOn(target);
}

void Stats::update(sf::Time dt) {                           // update the Stats' evolution
    counter += dt;
    if (counter > sf::seconds(getValueConfig()["stats"]["refresh rate"].toDouble())) {
        std::unordered_map<std::string, double> new_data;
        for (size_t i(0); i < graphs.size(); ++i) {
            new_data = getAppEnv().fetchData(labels.at(i));
            graphs[i]->updateData(counter, new_data);
        }
        counter = sf::Time::Zero;
    }

}

void Stats::reset() {                                       // reset the Stats
    counter = sf::Time::Zero;
    for (size_t i(0); i < graphs.size(); ++i) {
        graphs[i]->reset();
    }
}


// GETTER
std::string Stats::getCurrentTitle() const {                // get the current title
    return labels.at(id);
}


// CHANGERS
void Stats::setActive(int id) {                             // assign the value id to the current identifier
    this->id = id;
}

void Stats::next() {                                        // increment the current id
    if (id != (int)graphs.size() - 1) {  // change the id
        ++ id;
    }
    else id = 0;
}

void Stats::previous() {                                    // decrement the current id
    if (id != 0) {
        -- id;
    }
    else id = (int)graphs.size() - 1 ;
}

void Stats::addGraph(                                       // add a Graph to the collection of Graphs
  int id,
  const std::string &title,
  const std::vector<std::string> &series,
  double min,
  double max,
  const Vec2d &size
) {
    Graph* new_graph (new Graph(series, size, min, max));
    graphs[id].reset(new_graph);
    labels[id] = title;
    setActive(id);
}

