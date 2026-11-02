add_library(llts_strategy STATIC
        src/market_maker.cpp
)
target_include_directories(llts_strategy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_strategy PUBLIC llts_common)
llts_set_warnings(llts_strategy ON)

add_subdirectory(tests)