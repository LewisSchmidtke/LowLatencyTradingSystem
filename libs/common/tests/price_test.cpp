#include "LLTS/common/price.hpp"
#include <gtest/gtest.h>
#include <type_traits>

namespace lc = llts::common;

static_assert(std::is_trivially_copyable_v<lc::Price>, "Price must be trivially copyable");

TEST(Price, ParseTwoDecimals) {
    const auto p = lc::Price::convert_string_to_price("100.10");
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->get_cents(), 10010);
}

TEST(Price, ParseSingleDecimal) {
    const auto p = lc::Price::convert_string_to_price("100.1");
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->get_cents(), 10010);
}

TEST(Price, ParseLeadingZeroCents) {
    const auto p = lc::Price::convert_string_to_price("0.05");
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->get_cents(), 5);
}

TEST(Price, ParseNegative) {
    const auto p = lc::Price::convert_string_to_price("-2");
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->get_cents(), -200);
}

TEST(Price, ParseNegativeDecimal) {
    const auto p = lc::Price::convert_string_to_price("-0.5");
    ASSERT_TRUE(p.has_value());
    EXPECT_EQ(p->get_cents(), -50);
}

TEST(Price, ValidateOverflowBoundary) {
    const auto accept = lc::Price::convert_string_to_price("92233720368547758");
    ASSERT_TRUE(accept.has_value());
    EXPECT_EQ(accept->get_cents(), 9223372036854775800);

    EXPECT_FALSE(lc::Price::convert_string_to_price("92233720368547759").has_value());
}


TEST(Price, RejectEmpty) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("").has_value());
}

TEST(Price, RejectPeriod) {
    EXPECT_FALSE(lc::Price::convert_string_to_price(".").has_value());
}

TEST(Price, RejectMoreThanTwoDecimals) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("1.234").has_value());
}

TEST(Price, RejectMissingDecimals) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("5.").has_value());
}

TEST(Price, RejectTooLargeNumber) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("99999999999999999999").has_value());
}

TEST(Price, RejectNonNumericString) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("1a").has_value());
}

TEST(Price, RejectDoubleNegativeSign) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("--1").has_value());
}

TEST(Price, RejectNegativeSignAfterPeriod) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("12.-5").has_value());
}

TEST(Price, RejectDash) {
    EXPECT_FALSE(lc::Price::convert_string_to_price("-").has_value());
}

TEST(Price, FormatNegative) {
    EXPECT_EQ(lc::Price{-5}.convert_price_to_string(), "-0.05");
}

TEST(Price, FormatNormal) {
    EXPECT_EQ(lc::Price{11399}.convert_price_to_string(), "113.99");
}

TEST(Price, FormatZero) {
    EXPECT_EQ(lc::Price{0}.convert_price_to_string(), "0.00");
}

TEST(Price, FormatTrailingZero) {
    EXPECT_EQ(lc::Price{10010}.convert_price_to_string(), "100.10");
}
