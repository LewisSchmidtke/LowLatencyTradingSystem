#include "LLTS/common/price.hpp"
#include <gtest/gtest.h>
#include <type_traits>

namespace lc = llts::common;

static_assert(std::is_trivially_copyable_v<lc::Price>, "Price must be trivially copyable");
static_assert(lc::Price{}.get_cents() == 0, "Default Price must be 0 cents");
static_assert(lc::Price{1234}.get_cents() == 1234, "constexpr constructor must store cents");

// Testing the operators
static_assert(lc::Price{100} < lc::Price{200});
static_assert(lc::Price{-5} < lc::Price{0});
static_assert(lc::Price{0} < lc::Price{5});
static_assert(lc::Price{200} > lc::Price{100});
static_assert(lc::Price{-5} > lc::Price{-7});
static_assert(lc::Price{100} == lc::Price{100});
static_assert(lc::Price{-100} == lc::Price{-100});
static_assert(lc::Price{100} != lc::Price{101});
static_assert(lc::Price{100} != lc::Price{-100});
static_assert(lc::Price{100} >= lc::Price{100});
static_assert(lc::Price{100} <= lc::Price{100});
static_assert(lc::Price{-100} >= lc::Price{-100});
static_assert(lc::Price{-100} <= lc::Price{-100});

static_assert(!(lc::Price{100} < lc::Price{100}));
static_assert(!(lc::Price{100} > lc::Price{100}));
static_assert(!(lc::Price{100} != lc::Price{100}));

static_assert(lc::Price{10000}.add_ticks(3) == lc::Price{10003});
static_assert(lc::Price{10000}.subtract_ticks(3) == lc::Price{9997});
static_assert(lc::Price{10000}.ticks_above(lc::Price{9999}) == 1);
static_assert(lc::Price{10000}.add_ticks(-3) == lc::Price{9997});
static_assert(lc::Price{10000}.subtract_ticks(-3) == lc::Price{10003});

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

TEST(Price, AddTicksNormal) {
    EXPECT_EQ(lc::Price{10000}.add_ticks(3), lc::Price{10003});
    EXPECT_EQ(lc::Price{10000}.add_ticks(0), lc::Price{10000});
}

TEST(Price, AddTicksInitialPriceUnchanged) {
    const lc::Price base{10000};
    const lc::Price moved = base.add_ticks(10);
    EXPECT_EQ(moved, lc::Price{10010});
    EXPECT_EQ(base, lc::Price{10000});
}

TEST(Price, SubtractTicksNormal) {
    EXPECT_EQ(lc::Price{10000}.subtract_ticks(3), lc::Price{9997});
    EXPECT_EQ(lc::Price{10000}.subtract_ticks(0), lc::Price{10000});
}

TEST(Price, SubtractTicksInitialPriceUnchanged) {
    const lc::Price base{10000};
    const lc::Price moved = base.subtract_ticks(10);
    EXPECT_EQ(moved, lc::Price{9990});
    EXPECT_EQ(base, lc::Price{10000});
}

TEST(Price, SubtractAddTicksPriceUnchanged) {
    const auto base = lc::Price{10000};
    EXPECT_EQ(base.subtract_ticks(10).add_ticks(10), base);
}

TEST(Price, SubtractTicksBelowZero) {
    EXPECT_EQ(lc::Price{2}.subtract_ticks(5), lc::Price{-3});
}

TEST(Price, AddNegativeTicks) {
    EXPECT_EQ(lc::Price{10000}.add_ticks(-3), lc::Price{9997});
}

TEST(Price, SubtractNegativeTicks) {
    EXPECT_EQ(lc::Price{10000}.subtract_ticks(-3), lc::Price{10003});
}

TEST(Price, AddNegativeTicksEqualsSubtractTicks) {
    const lc::Price base{10000};
    const std::int64_t n = 7;
    EXPECT_EQ(base.add_ticks(-n), base.subtract_ticks(n));
    EXPECT_EQ(base.subtract_ticks(-n), base.add_ticks(n));
}

TEST(Price, AddNegativeTicksBelowZero) {
    EXPECT_EQ(lc::Price{2}.add_ticks(-5), lc::Price{-3});
}

TEST(Price, TicksAbovePositive) {
    EXPECT_EQ(lc::Price{10003}.ticks_above(lc::Price{10000}), 3);
}

TEST(Price, TicksAboveNegative) {
    EXPECT_EQ(lc::Price{10000}.ticks_above(lc::Price{10003}), -3);
}

TEST(Price, TicksAboveZero) {
    EXPECT_EQ(lc::Price{10000}.ticks_above(lc::Price{10000}), 0);
}

TEST(Price, AddTicksAndTicksAboveConsistency) {
    const std::int64_t n = 3;
    const std::int64_t a = 10000;
    EXPECT_EQ(lc::Price{a}.add_ticks(n).ticks_above(lc::Price{a}), n);
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
