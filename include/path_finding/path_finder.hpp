#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include "core/point2D.hpp"

#include <iostream>
#include <vector>

using namespace mas;
namespace path_finder {

    class MASPathFinder {
        public:
            MASPathFinder() = default;

            ~MASPathFinder() = default;

            virtual bool doSearch() = 0;
    };
} // namespace mas

#endif