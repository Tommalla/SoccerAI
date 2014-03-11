set(HEADERS
	AI.hpp
	AlphaBetaTree.hpp
	AIFactory.hpp
)

set(SOURCES
	AI.cpp
	AlphaBetaTree.cpp
	AIFactory.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
