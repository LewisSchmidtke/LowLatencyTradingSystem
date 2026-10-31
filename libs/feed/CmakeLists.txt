add_library(llts_feed STATIC
        src/md_codec.cpp
        src/sequence_tracker.cpp
        src/session_file.cpp
)
target_include_directories(llts_feed PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_feed PUBLIC llts_common)
llts_set_warnings(llts_feed ON)

add_subdirectory(tests)