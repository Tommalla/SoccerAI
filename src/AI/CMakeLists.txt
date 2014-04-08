set(HEADERS
	AI.hpp
	RandomAI.hpp
	AlphaBetaAI.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
	AlphaBetaAI.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
