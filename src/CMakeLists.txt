add_subdirectory(Engine)
add_subdirectory(AI)

set(HEADERS
)

set(SOURCES
	main.cpp
)

add_executable(SoccerAI ${SOURCES} ${HEADERS})