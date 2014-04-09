set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaAI.hpp
	objectiveFunctions.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaAI.cpp
	objectiveFunctions.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
