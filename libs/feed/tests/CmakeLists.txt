add_executable(llts_feed_tests
        md_codec_test.cpp
        sequence_tracker_test.cpp
        session_file_test.cpp
)
target_link_libraries(llts_feed_tests PRIVATE llts_feed GTest::gtest_main)
llts_set_warnings(llts_feed_tests OFF)
gtest_discover_tests(llts_feed_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "feed.")
