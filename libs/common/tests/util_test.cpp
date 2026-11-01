#include "LLTS/common/util.hpp"
#include <gtest/gtest.h>
#include <limits>

namespace lu = llts::common::util;

TEST(IsDigits, AcceptsOnlyDigits) {
    EXPECT_TRUE(lu::is_digits("0"));
    EXPECT_TRUE(lu::is_digits("123"));
    EXPECT_TRUE(lu::is_digits("007"));                    // leading zeros are still digits
    EXPECT_TRUE(lu::is_digits("99999999999999999999"));   // length doesn't matter; overflow is to_int's job
}

TEST(IsDigits, RejectsEmpty) {
    EXPECT_FALSE(lu::is_digits(""));
}

TEST(IsDigits, RejectsSigns) {
    EXPECT_FALSE(lu::is_digits("-1"));
    EXPECT_FALSE(lu::is_digits("+1"));
    EXPECT_FALSE(lu::is_digits("-"));
}

TEST(IsDigits, RejectsNonDigitCharacters) {
    EXPECT_FALSE(lu::is_digits("1a"));
    EXPECT_FALSE(lu::is_digits("a1"));
    EXPECT_FALSE(lu::is_digits("1.5"));
    EXPECT_FALSE(lu::is_digits(" 1"));    // whitespace at either end
    EXPECT_FALSE(lu::is_digits("1 "));
}

TEST(IsDigits, RejectsCharactersNextToDigitRange) {
    EXPECT_FALSE(lu::is_digits("/"));     // '/' is the character just before '0'
    EXPECT_FALSE(lu::is_digits(":"));     // ':' is the character just after '9'
}

TEST(ToInt, AcceptNormalBehavior) {
    EXPECT_EQ(lu::to_int("0"), 0);
    EXPECT_EQ(lu::to_int("442"), 442);
}

TEST(ToInt, AcceptBoundaryInt) {
    EXPECT_EQ(lu::to_int("9223372036854775807"), std::numeric_limits<std::int64_t>::max());
    EXPECT_EQ(lu::to_int("-9223372036854775808"), std::numeric_limits<std::int64_t>::min());
}

TEST(ToInt, RejectOverflow) {
    EXPECT_FALSE(lu::to_int("9223372036854775808"));
    EXPECT_FALSE(lu::to_int("-9223372036854775809"));
}

TEST(ToInt, RejectTrailingCharacters) {
    EXPECT_FALSE(lu::to_int("12a"));
    EXPECT_FALSE(lu::to_int("12 "));
}

TEST(SplitString, AcceptNormalBehavior) {
    EXPECT_EQ(lu::split_string("a.b", '.'), (std::vector<std::string>{"a", "b"}));
    EXPECT_EQ(lu::split_string("a.", '.'), (std::vector<std::string>{"a", ""}));
    EXPECT_EQ(lu::split_string(".b", '.'), (std::vector<std::string>{"", "b"}));
}

TEST(CanAdd, AcceptNormalBehavior) {
    EXPECT_TRUE(lu::can_add(2, 3));
    EXPECT_TRUE(lu::can_add(-5, 5));
    EXPECT_TRUE(lu::can_add(-2, -3));
    EXPECT_TRUE(lu::can_add(0, 0));
}

TEST(CanAdd, AcceptExactlyAtBoundary) {
    constexpr auto MAX = std::numeric_limits<std::int64_t>::max();
    constexpr auto MIN = std::numeric_limits<std::int64_t>::min();

    EXPECT_TRUE(lu::can_add(MAX, 0));
    EXPECT_TRUE(lu::can_add(MIN, 0));
    EXPECT_TRUE(lu::can_add(MAX - 1, 1));   // lands exactly on MAX
    EXPECT_TRUE(lu::can_add(MIN + 1, -1));  // lands exactly on MIN
    EXPECT_TRUE(lu::can_add(MAX, MIN));     // opposite signs can never overflow
}

TEST(CanAdd, RejectPositiveOverflow) {
    constexpr auto MAX = std::numeric_limits<std::int64_t>::max();

    EXPECT_FALSE(lu::can_add(MAX, 1));
    EXPECT_FALSE(lu::can_add(1, MAX));      // order of arguments must not matter
    EXPECT_FALSE(lu::can_add(MAX, MAX));
}

TEST(CanAdd, RejectNegativeOverflow) {
    constexpr auto MIN = std::numeric_limits<std::int64_t>::min();

    EXPECT_FALSE(lu::can_add(MIN, -1));
    EXPECT_FALSE(lu::can_add(-1, MIN));
    EXPECT_FALSE(lu::can_add(MIN, MIN));
}