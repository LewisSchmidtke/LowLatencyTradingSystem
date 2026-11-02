#pragma once

#include <cstdint>
namespace llts::common {
using InstrumentId = std::uint16_t;
using ParticipantId = std::uint8_t; // 0 = Simulator, 1 = Trader
using ClientOrderId = std::uint64_t;
using ExchangeOrderId = std::uint64_t;
using Qty = std::uint32_t;
using Position = std::int64_t;
using ClockTicks = std::uint64_t;

constexpr ParticipantId kSimulatorParticipant = 0;
constexpr ParticipantId kTraderParticipant = 1;

enum class Side : std::uint8_t { Buy, Sell };

constexpr Side opposite_side(Side side) {
    if (side == Side::Buy) {
        return Side::Sell;
    }
    return Side::Buy;
}
} // namespace llts::common
