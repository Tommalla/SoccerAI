set(HEADERS
	AI.hpp
	AlphaBetaTree.hpp
)

set(SOURCES
	AI.cpp
	AlphaBetaTree.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
