#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <cstdint>

namespace llts::common::util {

[[nodiscard]] std::vector<std::string> split_string(std::string_view string_input, char delimiter);
[[nodiscard]] bool is_digits(std::string_view s);
[[nodiscard]] std::optional<std::int64_t> to_int(std::string_view str);
[[nodiscard]] bool can_add(std::int64_t a, std::int64_t b);

} // namespace llts::common::util