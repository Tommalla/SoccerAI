add_subdirectory(Engine)
add_subdirectory(AI)

add_executable(SoccerAI main.cpp)
target_link_libraries(SoccerAI Engine AI)

add_executable(judge judge.cpp)
target_link_libraries(judge Engine AI)