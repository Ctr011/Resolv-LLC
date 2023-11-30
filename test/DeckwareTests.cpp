#include <gtest/gtest.h>
#include "DeckwareTests.hpp"

//  Base COntainerSlot Tests
TEST(ContainerSlots, Base_ContainerSlot_Objects){
    EXPECT_NO_THROW(new Container("Container", 100, 1, 1, Origin::BAY));
    EXPECT_NO_THROW(new NANSlot(1, 1, Origin::BUFFER));
    EXPECT_NO_THROW(new EmptySlot(1, 1, Origin::BUFFER));
}

TEST(ContainerSlots, Container_Limits){
    EXPECT_THROW(new Container("BAD_MASS", 10000000, 1, 1, Origin::BAY), std::invalid_argument);
    EXPECT_THROW(new Container("BAD_MASS", -1, 1, 1, Origin::BAY), std::invalid_argument);
    EXPECT_THROW(new Container("NAN", 100, 1, 1, Origin::BAY), std::invalid_argument);
    EXPECT_THROW(new Container("UNUSED", 100, 1, 1, Origin::BAY), std::invalid_argument);
    EXPECT_THROW(new Container("", 100, 1, 1, Origin::BAY), std::invalid_argument);

    //  Construct long name here
    std::string bad_name = "";
    for(int i = 0; i <= 300; i++){
        bad_name += "A";
    }
    EXPECT_THROW(new Container(bad_name, 100, 1, 1, Origin::BAY), std::invalid_argument);

    //  Now the x and y positions
    EXPECT_THROW(new Container("BAD_BAY_X", 100, 0, 1, Origin::BAY), std::invalid_argument);
    EXPECT_THROW(new Container("BAD_BAY_Y", 100, 1, 0, Origin::BAY), std::invalid_argument);

    EXPECT_THROW(new Container("BAD_BAY_X", 100, 0, 100, Origin::BUFFER), std::invalid_argument);
    EXPECT_THROW(new Container("BAD_BAY_Y", 100, 100, 0, Origin::BUFFER), std::invalid_argument);
}

TEST(ContainerSlots, ContainerSlot_EdgeCases){

    //  Names
    EXPECT_NO_THROW(new Container("nAn", 100, 1, 1, Origin::BAY));
    EXPECT_NO_THROW(new Container("unUseD", 100, 1, 1, Origin::BUFFER));
    EXPECT_NO_THROW(new Container(".", 100, 1, 1, Origin::BUFFER));
    EXPECT_NO_THROW(new Container(" ", 100, 1, 1, Origin::BUFFER));

    //  Weights
    EXPECT_NO_THROW(new Container("MAX_WEIGHT", 99999, 1, 1, Origin::BUFFER));
    EXPECT_NO_THROW(new Container("MIN_WEIGHT", 0, 1, 1, Origin::BAY));
}