add_library(llts_gateway STATIC
        src/order_tracker.cpp
        src/order_gateway.cpp
)
target_include_directories(llts_gateway PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_gateway PUBLIC llts_common)
llts_set_warnings(llts_gateway ON)

add_subdirectory(tests)