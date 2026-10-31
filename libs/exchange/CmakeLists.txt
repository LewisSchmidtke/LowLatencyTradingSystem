add_library(llts_exchange STATIC
        src/order_book.cpp
        src/matching_engine.cpp
)
target_include_directories(llts_exchange PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_exchange PUBLIC llts_common)
llts_set_warnings(llts_exchange ON)

add_subdirectory(tests)