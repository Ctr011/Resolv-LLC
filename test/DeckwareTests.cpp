#include <gtest/gtest.h>
#include "DeckwareTests.hpp"

TEST(ContainerSlot, Base){
    ASSERT_NO_THROW(new Container("Container", 100, 0, 0, Origin::BAY));
}