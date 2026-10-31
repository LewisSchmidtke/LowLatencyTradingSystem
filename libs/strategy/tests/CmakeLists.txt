add_executable(llts_strategy_tests
        market_maker_test.cpp
)
target_link_libraries(llts_strategy_tests PRIVATE llts_strategy GTest::gtest_main)
llts_set_warnings(llts_strategy_tests OFF)
gtest_discover_tests(llts_strategy_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "strategy.")
