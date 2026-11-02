#include "LLTS/common/config.hpp"
#include <gtest/gtest.h>
#include <type_traits>

namespace lc = llts::common;

static_assert(std::is_aggregate_v<lc::RunConfig>);
static_assert(std::is_aggregate_v<lc::ExchangeConfig>);
static_assert(std::is_aggregate_v<lc::CoreConfig>);
static_assert(std::is_aggregate_v<lc::LogConfig>);
static_assert(std::is_aggregate_v<lc::InstrumentConfig>);
static_assert(std::is_aggregate_v<lc::SimConfig>);
static_assert(std::is_aggregate_v<lc::StrategyConfig>);
static_assert(std::is_aggregate_v<lc::RiskConfig>);
static_assert(std::is_aggregate_v<lc::SystemConfig>);

TEST(PriceLevels, WideBandGivesTenThousandAndOne) {
    const lc::InstrumentConfig instrument_c{
        .symbol = "AAPL",
        .min_price = lc::Price{5'000},
        .max_price = lc::Price{15'000},
        .start_mid = lc::Price{10'000},
    };
    const std::size_t levels = lc::nr_of_price_levels(instrument_c);
    EXPECT_EQ(levels, 10'001U);
}

TEST(PriceLevels, SmallBandCountsBothEnds) {
    const lc::InstrumentConfig instrument_c{
        .min_price = lc::Price{500},
        .max_price = lc::Price{502},
    };
    const std::size_t levels = lc::nr_of_price_levels(instrument_c);
    EXPECT_EQ(levels, 3U);
}

TEST(PriceLevels, SingleLevelGives1) {
    const lc::InstrumentConfig instrument_c{
        .min_price = lc::Price{500},
        .max_price = lc::Price{500},
    };
    const std::size_t levels = lc::nr_of_price_levels(instrument_c);
    EXPECT_EQ(levels, 1U);
}

TEST(ConfigDefaults, SystemConfigHasNoInstruments) {
    const lc::SystemConfig system_c;
    EXPECT_TRUE(system_c.instruments.empty());
}

TEST(ConfigDefaults, CoresDefaultToNoPinning) {
    const lc::CoreConfig core_c;
    EXPECT_EQ(core_c.exchange, -1);
    EXPECT_EQ(core_c.logger, -1);
    EXPECT_EQ(core_c.market_data, -1);
    EXPECT_EQ(core_c.trading, -1);
}

TEST(ConfigDefaults, LogLevelDefaultsToInfo) {
    const lc::LogConfig log_c;
    EXPECT_EQ(log_c.level, lc::LogLevel::Info);
}

TEST(ConfigInit, UnsetFieldsKeepDefaults) {
    const lc::SimConfig sim_c{
        .messages_per_second = 0,
        .max_live_orders = 100,
    };

    EXPECT_EQ(sim_c.messages_per_second, 0U);
    EXPECT_EQ(sim_c.max_live_orders, 100U);
    // Still equal to the default values
    EXPECT_EQ(sim_c.weight_passive, 70U);
    EXPECT_EQ(sim_c.weight_cancel, 20U);
    EXPECT_EQ(sim_c.passive_depth_ticks, 20);
    EXPECT_EQ(sim_c.max_order_qty, 500U);
}