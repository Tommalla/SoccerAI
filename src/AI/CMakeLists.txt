set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaAI.hpp
	objectiveFunctions.hpp
	AIFactory.hpp
	Judge.hpp
	Status.hpp
	MemoryManager.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaAI.cpp
	objectiveFunctions.cpp
	AIFactory.cpp
	Judge.cpp
	Status.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
target_link_libraries(AI Engine)
