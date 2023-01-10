#ifndef MAS_PATH_FINDER_HPP_
#define MAS_PATH_FINDER_HPP_

#include <iostream>
#include <vector>

namespace mas_path_finder
{
    class MASPathFinder {
        public:
            MASPathFinder()
            {

            }

            ~MASPathFinder() = default;

            virtual doSearch() = 0;
    };
}

#endif