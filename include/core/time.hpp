#ifndef MAS_CORE_TIME_HPP_
#define MAS_CORE_TIME_HPP_

#include <SFML/System/Clock.hpp>

namespace mas {
    class TimeHandler {
    public:
        TimeHandler(double update_rate = 60.0)
            : update_rate_hz_(update_rate)
        {
        }

        void setUpdateRate(const double frequency)
        {
            update_rate_hz_ = frequency;
            update();
        }

        double getUpdateRate() const { return update_rate_hz_; }

        double getDuration_s() const { return duration_s_; }

    private:
        double update_rate_hz_ = 60;
        double duration_s_ = 1.0f / 60;
        sf::Clock start_time_{};

        void update() { duration_s_ = 1.0f / update_rate_hz_; }
    };

} // namespace mas

#endif