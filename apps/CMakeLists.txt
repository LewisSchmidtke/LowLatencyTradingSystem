add_executable(llts_trader
        trader/main.cpp
        trader/threads.cpp
)
target_link_libraries(llts_trader PRIVATE
        llts_common llts_exchange llts_feed llts_sim llts_book
        llts_strategy llts_risk llts_gateway llts_logging
)
llts_set_warnings(llts_trader ON)

add_executable(llts_session_gen session_gen/main.cpp)
target_link_libraries(llts_session_gen PRIVATE
        llts_common llts_exchange llts_sim llts_feed llts_book
)
llts_set_warnings(llts_session_gen ON)

add_executable(llts_replay replay/main.cpp)
target_link_libraries(llts_replay PRIVATE llts_common llts_feed llts_book)
llts_set_warnings(llts_replay ON)