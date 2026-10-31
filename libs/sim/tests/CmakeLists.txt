add_executable(llts_sim_tests
        order_flow_generator_test.cpp
)
target_link_libraries(llts_sim_tests PRIVATE llts_sim GTest::gtest_main)
llts_set_warnings(llts_sim_tests OFF)
gtest_discover_tests(llts_sim_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "sim.")
