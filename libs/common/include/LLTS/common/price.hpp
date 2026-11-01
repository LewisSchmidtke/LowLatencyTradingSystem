#pragma once

#include "LLTS/common/types.hpp"

#include <compare>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace llts::common {

class Price {
private:
    std::int64_t cents{0};

public:
    constexpr Price() = default;
    constexpr explicit Price(std::int64_t amount) : cents(amount) {}

    [[nodiscard]] constexpr std::int64_t get_cents() const { return cents; }

    constexpr auto operator<=>(const Price&) const = default;
    constexpr bool operator==(const Price&) const = default;

    [[nodiscard]] static std::optional<Price>
    convert_string_to_price(std::string_view string_input);
    [[nodiscard]] std::string convert_price_to_string() const;

    /* We will not check for overflow after adding or subtracting ticks here as this is completely
     * unrealistic that adding or subtracting ticks will pass around 92 quadrillion dollars*/
    [[nodiscard]] constexpr Price add_ticks(Ticks ticks) const {
        const std::int64_t new_amount = static_cast<std::int64_t>(ticks) + cents;
        return Price{new_amount};
    }

    [[nodiscard]] constexpr Price subtract_ticks(Ticks ticks) const {
        const std::int64_t new_amount = cents - static_cast<std::int64_t>(ticks);
        return Price{new_amount};
    }

    [[nodiscard]] constexpr std::int64_t ticks_above(Price other_price) const {
        const int64_t tick_difference = cents - other_price.cents;
        return tick_difference;
    }
};
} // namespace llts::common