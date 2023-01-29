#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include <iostream>
#include <vector>

namespace path_finder {

    class MASPathFinder {
        public:
            MASPathFinder() = default;

            ~MASPathFinder() = default;

            virtual bool doSearch() = 0;
    };
} // namespace mas

#endif