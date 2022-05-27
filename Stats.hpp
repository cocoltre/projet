#include <iostream>
#include "Stats/Graph.hpp"
#include <memory>
#include "Interface/Drawable.hpp"
#include "Interface/Updatable.hpp"
#include <map>
#pragma once

class Stats : public Drawable, public Updatable {
private :
    std::map<int, std::unique_ptr<Graph>> graphs;   // the collection of Graphs
    std::map<int, std::string> labels;              // the collection of labels related to the Graphs
    int id;                                         // the id of the current Graph
    sf::Time counter;                               // the counter for updating the data

public :

    // DESTRUCTOR
    ~Stats() {}         // destructor


    // RELATIVE TO EVOLUTION
    /*!
     * \brief draw the Stats
     * \param target the environment where to draw
     */
    virtual void drawOn(sf::RenderTarget& target) const override ;

    /*!
     * \brief update the Stats' evolution
     * \param dt the small amount of time
     */
    void update(sf::Time dt) override ;

    /*!
     * \brief reset the Stats
     */
    void reset();


    // GETTER
    /*!
     * \brief get the current title
     * \return the current title
     */
    std::string getCurrentTitle() const;


    // CHANGERS
    /*!
     * \brief assign the value id to the current identifier
     * \param id the new identifier
     */
    void setActive(int id);

    /*!
     * \brief increment the current id
     */
    void next();

    /*!
     * \brief decrement the current id
     */
    void previous();

    /*!
     * \brief add a Graph to the collection of Graphs
     * \param id the id of this Graph
     * \param title the title of this Graph
     * \param series the series of this Graph
     * \param min the minimal value from which the curve points are displayed
     * \param max the maximal value under which the curve points are displayed
     * \param size the dimensions of the graphics window
     */
    void addGraph(
      int id,
      const std::string &title,
      const std::vector<std::string> &series,
      double min,
      double max,
      const Vec2d &size
    );

};
