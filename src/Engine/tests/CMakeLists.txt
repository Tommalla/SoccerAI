set(SOURCES
	BoardTest.cpp
)

add_executable(BoardTest ${SOURCES})
target_link_libraries(BoardTest Engine)