#include "LLTS/common/types.hpp"
#include <gtest/gtest.h>

namespace lc = llts::common;

static_assert(sizeof(lc::Side) == 1, "Side must be 1 byte");
static_assert(lc::opposite_side(lc::Side::Buy) == lc::Side::Sell, "Opposite of Buy must be Sell");
static_assert(lc::opposite_side(lc::Side::Sell) == lc::Side::Buy, "Opposite of Sell must be Buy");
static_assert(lc::opposite_side(lc::opposite_side(lc::Side::Buy)) == lc::Side::Buy,
              "Opposite of the opposite of Buy must be Buy");

TEST(Types, OppositeSide) {
    EXPECT_EQ(lc::opposite_side(lc::Side::Buy), lc::Side::Sell);
    EXPECT_EQ(lc::opposite_side(lc::Side::Sell), lc::Side::Buy);
}
