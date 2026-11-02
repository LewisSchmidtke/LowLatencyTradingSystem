add_executable(llts_logging_tests
        async_logger_test.cpp
)
target_link_libraries(llts_logging_tests PRIVATE llts_logging GTest::gtest_main)
llts_set_warnings(llts_logging_tests OFF)
gtest_discover_tests(llts_logging_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "logging.")
