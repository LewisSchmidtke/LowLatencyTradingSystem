#include "LLTS/common/config.hpp"

namespace llts::common {

std::size_t nr_of_price_levels(const InstrumentConfig& instrument) {
    // We will have guaranteed that max > min through the config reader, so we can static_cast safely
    return static_cast<std::size_t>(instrument.max_price.ticks_above(instrument.min_price)) + 1;
}
} // namespace llts::common
