set(HEADERS
	engine.hpp
	Board.hpp
)

set(SOURCES
	engine.cpp
	Board.cpp
)

add_library(Engine ${HEADERS} ${SOURCES})
add_subdirectory(tests)