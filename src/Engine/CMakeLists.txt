set(HEADERS
	engine.hpp
	Board.hpp
)

set(SOURCES
	Board.cpp
)

add_library(Engine ${HEADERS} ${SOURCES})
add_subdirectory(tests)