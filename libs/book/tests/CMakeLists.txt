add_executable(llts_book_tests
        book_builder_test.cpp
        book_snapshot_test.cpp
)
target_link_libraries(llts_book_tests PRIVATE llts_book GTest::gtest_main)
llts_set_warnings(llts_book_tests OFF)
gtest_discover_tests(llts_book_tests DISCOVERY_MODE PRE_TEST DISCOVERY_TIMEOUT 30 TEST_PREFIX "book.")
