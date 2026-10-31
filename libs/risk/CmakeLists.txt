add_library(llts_risk STATIC
        src/token_bucket.cpp
        src/risk_gate.cpp
)
target_include_directories(llts_risk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_risk PUBLIC llts_common)
llts_set_warnings(llts_risk ON)

add_subdirectory(tests)