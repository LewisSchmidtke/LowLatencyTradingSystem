add_library(llts_book STATIC
        src/book_builder.cpp
        src/book_snapshot.cpp
)
target_include_directories(llts_book PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(llts_book PUBLIC llts_common)
llts_set_warnings(llts_book ON)

add_subdirectory(tests)