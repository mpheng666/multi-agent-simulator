#ifndef MAS_PATH_FINDING_DFS_HPP_
#define MAS_PATH_FINDING_DFS_HPP_

#include "path_finder.hpp"
#include <stack>

namespace mas {
  class DepthFirstSearch : public MASPathFinder {
public:
    DepthFirstSearch() {}
    ~DepthFirstSearch() {}

    bool doSearch() override { return true; }

    std::stack<Index> getPath() const { return path_; }

private:
    std::stack<Index> path_;
  };
} // namespace mas

#endif