#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <cstdint>

namespace llts::common::util {

std::vector<std::string> split_string(std::string_view string_input, char delimiter);
bool is_digits(std::string_view s);
std::optional<std::int64_t> to_int(std::string_view str);
bool can_add(std::int64_t a, std::int64_t b);

} // namespace llts::common::util