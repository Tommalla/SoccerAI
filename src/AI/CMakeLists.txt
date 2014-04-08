set(HEADERS
	AI.hpp
	RandomAI.hpp
)

set(SOURCES
	AI.cpp
	RandomAI.cpp
)

add_library(AI ${HEADERS} ${SOURCES})
