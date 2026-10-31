add_library(llts_logging STATIC
        src/async_logger.cpp
)
target_include_directories(llts_logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_logging PUBLIC llts_common)
llts_set_warnings(llts_logging ON)

add_subdirectory(tests)