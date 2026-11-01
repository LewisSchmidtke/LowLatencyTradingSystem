#include "LLTS/common/price.hpp"
#include "LLTS/common/util.hpp"

#include <format>
#include <limits>
#include <vector>

namespace llts::common {

std::optional<Price> Price::convert_string_to_price(std::string_view string_input) {
    std::string_view s = string_input;
    const bool is_negative = s.starts_with('-');
    if (is_negative)
        s.remove_prefix(1);

    const std::vector<std::string> string_parts = util::split_string(s, '.');

    // Cases resulting from wrong input
    if (string_parts.size() == 0 or string_parts.size() > 2) {
        return std::nullopt;
    }

    // catches inputs like "number." or "number.123"
    if (string_parts.size() == 2 and
        (string_parts[1].length() > 2 or string_parts[1].length() == 0)) {
        return std::nullopt;
    }

    // catches inputs with nothing before the ., e.g. ".50" or "."
    if (string_parts[0].length() == 0) {
        return std::nullopt;
    }

    // catches all non numeric characters
    for (const std::string_view part : string_parts) {
        if (!util::is_digits(part)) {
            return std::nullopt;
        }
    }

    // We check if we can safely multiply dollars by 100 to represent the dollar amount in cents
    const std::optional<std::int64_t> dollars_opt = util::to_int(string_parts[0]);
    if (!dollars_opt) {
        return std::nullopt;
    } // Too many digits to fit into int64
    const std::int64_t dollars = *dollars_opt;
    // We check that we are able to multiply the dollar amount by 100 to represent cents safely
    if (dollars > std::numeric_limits<std::int64_t>::max() / 100) {
        return std::nullopt;
    }

    const std::int64_t dollar_amount = dollars * 100;
    std::int64_t total_amount = dollar_amount;

    if (string_parts.size() > 1) {
        std::int64_t cent_amount = util::to_int(string_parts[1]).value();
        // If length 1 given as .2 which would be 20 cents so *10
        if (string_parts[1].length() == 1) {
            cent_amount *= 10;
        }
        if (util::can_add(cent_amount, dollar_amount) == false) {
            return std::nullopt;
        }
        total_amount = dollar_amount + cent_amount;
    }

    total_amount = is_negative ? total_amount * -1 : total_amount;

    return Price{total_amount};
}

std::string Price::convert_price_to_string() const {
    const bool is_negative = cents < 0;

    /* I previously had abs(cents), but because int64_t has one more value on the negative side,
     * calling abs on the minimum would not be able to fit in the positive side */
    const std::uint64_t magnitude =
        cents < 0 ? 0 - static_cast<std::uint64_t>(cents) : static_cast<std::uint64_t>(cents);
    const std::string dollar_str = std::to_string(magnitude / 100);
    const std::string cent_str = std::format("{:02}", magnitude % 100);
    const std::string sign = is_negative ? "-" : "";

    return sign + dollar_str + "." + cent_str;
}
} // namespace llts::common
