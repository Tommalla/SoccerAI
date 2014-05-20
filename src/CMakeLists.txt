add_subdirectory(Engine)
add_subdirectory(AI)

add_executable(judge judge.cpp)
target_link_libraries(judge Engine AI)

add_executable(mctsEvolve mctsEvolve.cpp)
target_link_libraries(mctsEvolve Engine AI)

add_executable(SoccerAI main.cpp)
set_target_properties(SoccerAI PROPERTIES
	COMPILE_FLAGS "${FINAL_FLAGS} -DGRAPH_MAP_MCTS_AI")
target_link_libraries(SoccerAI Engine AI)

add_executable(AlphaBeta main.cpp)
set_target_properties(AlphaBeta PROPERTIES
	COMPILE_FLAGS "${FINAL_FLAGS} -DGRAPH_ALPHA_BETA_AI")
target_link_libraries(AlphaBeta Engine AI)

add_executable(MCTS main.cpp)
set_target_properties(MCTS PROPERTIES
	COMPILE_FLAGS "${FINAL_FLAGS} -DSEQUENTIAL_TREE_MCTS_AI")
target_link_libraries(MCTS Engine AI)