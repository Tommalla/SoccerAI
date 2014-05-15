add_subdirectory(Engine)
add_subdirectory(AI)

set (CMAKE_CXX_FLAGS "${FINAL_FLAGS} -DSEQUENTIAL_TREE_MCTS_AI")
add_executable(SoccerAI main.cpp)
target_link_libraries(SoccerAI Engine AI)

add_executable(judge judge.cpp)
target_link_libraries(judge Engine AI)

set (CMAKE_CXX_FLAGS "${FINAL_FLAGS} -DGRAPH_ALPHA_BETA_AI")
add_executable(AlphaBeta main.cpp)
target_link_libraries(AlphaBeta Engine AI)

set (CMAKE_CXX_FLAGS "${FINAL_FLAGS} -DSEQUENTIAL_TREE_MCTS_AI")
add_executable(MCTS main.cpp)
target_link_libraries(MCTS Engine AI)