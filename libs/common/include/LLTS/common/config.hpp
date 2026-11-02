#pragma once

#include "LLTS/common/types.hpp"
#include "LLTS/common/price.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace llts::common {

enum class LogLevel : std::uint8_t { Debug, Info, Warn, Error };

struct RunConfig {
    std::uint32_t duration_seconds {30};
    std::uint64_t seed {777};
};

struct ExchangeConfig {
    std::size_t max_orders_per_instrument {200'000};
};

// -1 means dont pin these
struct CoreConfig {
    int exchange {-1};
    int market_data {-1};
    int trading {-1};
    int logger {-1};
};

struct LogConfig {
    std::string file {"llt.log"};
    LogLevel level {LogLevel::Info};
};

struct InstrumentConfig {
    std::string symbol {};
    Price min_price {};
    Price max_price {};
    Price start_mid {};
};

struct SimConfig {
    std::uint32_t messages_per_second {200'000};
    std::uint32_t weight_passive {70};
    std::uint32_t weight_aggressive {10};
    std::uint32_t weight_cancel {20};
    std::size_t max_live_orders {5000};
    std::int64_t passive_depth_ticks {20};
    Qty max_order_qty {500};
    std::uint32_t mid_move_percent {5};
};

struct StrategyConfig {
    Qty quote_qty {100};
    std::int64_t half_spread_ticks {3};
    std::int64_t skew_ticks_per_100_shares {1};
    std::int64_t requote_threshold_ticks {1};
    Position max_position {1000};
};

struct RiskConfig {
    Qty max_order_qty {500};
    Position max_position {2000};
    std::size_t max_open_orders {8};
    Price max_notional {100'000'000};
    std::int64_t price_collar_ticks {50};
    std::uint32_t orders_per_second {1000};
    std::uint32_t burst {100};
};

struct SystemConfig {
    RunConfig run {};
    SimConfig sim {};
    ExchangeConfig exchange {};
    StrategyConfig strategy {};
    RiskConfig risk {};
    CoreConfig cores {};
    LogConfig log {};
    std::vector<InstrumentConfig> instruments {};
};

[[nodiscard]] std::size_t nr_of_price_levels(const InstrumentConfig& instrument);

} // namespace llts::common
