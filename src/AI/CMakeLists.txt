set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaAI.hpp
	objectiveFunctions.hpp
	AIFactory.hpp
	judge.hpp
	Status.hpp
	MemoryManager.hpp
	ArrayMemoryManager.hpp
	MCTSAI.hpp
	SequentialTreeMCTSAI.hpp
	TranspositionTable.hpp
	TreeAlphaBetaAI.hpp
	GraphAlphaBetaAI.hpp
	GraphMapMCTSAI.hpp
	PseudoDynamicArrayMemoryManager.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaAI.cpp
	objectiveFunctions.cpp
	AIFactory.cpp
	judge.cpp
	Status.cpp
	MCTSAI.cpp
	SequentialTreeMCTSAI.cpp
	TreeAlphaBetaAI.cpp
	GraphAlphaBetaAI.cpp
	GraphMapMCTSAI.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
target_link_libraries(AI Engine)
