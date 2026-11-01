#include "LLTS/common/util.hpp"
#include <charconv>
#include <ranges>
#include <optional>
#include <string_view>
#include <limits>
#include <algorithm>

namespace llts::common::util {

std::vector<std::string> split_string(std::string_view string_input, char delimiter) {
    std::vector<std::string> string_parts;

    for (auto part : string_input | std::views::split(delimiter)) {
        string_parts.emplace_back(part.begin(), part.end());
    }

    return string_parts;
}

bool is_digits(std::string_view s) {
    return !s.empty() && std::ranges::all_of(s, [](char c) { return c >= '0' && c <= '9'; });
}

// We define to_int instead of using std::stoi because it is faster and doesnt allocate memory
std::optional<std::int64_t> to_int(std::string_view str) {
    std::int64_t value;

    auto [ptr, ec] = std::from_chars(
        str.data(), str.data() + str.size(), value
    );

    if (ec != std::errc{} || ptr != str.data() + str.size())
        return std::nullopt;

    return value;
}

// we use this function to check if we can add two numbers a,b without overflow
bool can_add(std::int64_t a, std::int64_t b) {
    constexpr auto MAX = std::numeric_limits<std::int64_t>::max();
    constexpr auto MIN = std::numeric_limits<std::int64_t>::min();

    if (b > 0 && a > MAX - b)
        return false; // Positive overflow

    if (b < 0 && a < MIN - b)
        return false; // Negative overflow

    return true;
}

} // namespace llts::common::util
