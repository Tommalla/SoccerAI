set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaNode.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaNode.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
