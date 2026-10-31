add_library(llts_sim STATIC
        src/order_flow_generator.cpp
)
target_include_directories(llts_sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_sim PUBLIC llts_common)
llts_set_warnings(llts_sim ON)

add_subdirectory(tests)