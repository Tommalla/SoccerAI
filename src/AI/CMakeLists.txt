set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaTree.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaTree.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
