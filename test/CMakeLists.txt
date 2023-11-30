cmake_minimum_required(VERSION 3.8)

set(This DeckwareTests)

set(Sources
    DeckwareTests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    Deckware
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
