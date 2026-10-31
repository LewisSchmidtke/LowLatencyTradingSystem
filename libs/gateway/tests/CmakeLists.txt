add_executable(llts_gateway_tests
        order_tracker_test.cpp
        order_gateway_test.cpp
)
target_link_libraries(llts_gateway_tests PRIVATE llts_gateway GTest::gtest_main)
llts_set_warnings(llts_gateway_tests OFF)
gtest_discover_tests(llts_gateway_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "gateway.")
