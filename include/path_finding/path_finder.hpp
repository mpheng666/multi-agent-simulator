#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include "core/grid.hpp"
#include "direction.hpp"
#include <array>
#include <iostream>
#include <vector>
namespace mas {
  class MASPathFinder {
public:
    MASPathFinder() = default;

    ~MASPathFinder() = default;

    virtual bool doSearch() = 0;

    void checkNeighbours(const Grid& current) {
      if(current.getPosition())
    }

    void step() {}

    Grid getStart() const { return start_; }
    Grid getGoal() const { return goal_; }
    void setStart(const Grid& start) { start_ = start; }
    void setGoal(const Grid& goal) { goal_ = goal; }

private:
    Grid start_;
    Grid goal_;

    PathFinderDirection direction_;
    std::vector<Grid> found_path_;
  };
} // namespace mas

#endif