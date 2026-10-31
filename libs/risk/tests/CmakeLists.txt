add_executable(llts_risk_tests
        token_bucket_test.cpp
        risk_gate_test.cpp
)
target_link_libraries(llts_risk_tests PRIVATE llts_risk GTest::gtest_main)
llts_set_warnings(llts_risk_tests OFF)
gtest_discover_tests(llts_risk_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "risk.")
