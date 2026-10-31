add_executable(llts_exchange_tests
        order_book_test.cpp
        matching_engine_test.cpp
)
target_link_libraries(llts_exchange_tests PRIVATE llts_exchange GTest::gtest_main)
llts_set_warnings(llts_exchange_tests OFF)
gtest_discover_tests(llts_exchange_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "exchange.")
