#ifndef MAS_PATH_FINDING_DIRECTION_HPP_
#define MAS_PATH_FINDING_DIRECTION_HPP_

#include <array>

namespace mas {
    enum class PathFinderDirection { CARDINAL, ORDINAL };

    struct CardinalStep {
        static constexpr std::array<std::array<int, 2>, 4> steps{{{1, 0}, {0, 1}, {-1, 0}, {0, -1}}};
    };
} // namespace mas

#endif