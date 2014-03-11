set(HEADERS
	constants.hpp
	Board.hpp
)

set(SOURCES
	Board.cpp
)

add_library(Engine ${HEADERS} ${SOURCES})