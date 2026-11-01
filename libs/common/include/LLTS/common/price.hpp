#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace llts::common {

class Price {
private:
    std::int64_t cents;

public:
    explicit Price(std::int64_t amount = 0) : cents(amount) {}

    constexpr std::int64_t get_cents() const { return cents; }

    static std::optional<Price> convert_string_to_price(std::string_view string_input);
    std::string convert_price_to_string() const;
};
}