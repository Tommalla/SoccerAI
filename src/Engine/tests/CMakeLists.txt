add_executable(BoardTest BoardTest.cpp)
target_link_libraries(BoardTest Engine)

add_executable(RandomTest RandomTest.cpp)
target_link_libraries(RandomTest Engine)

add_executable(engineTest engineTest.cpp)
target_link_libraries(engineTest Engine)

add_executable(HashTest HashTest.cpp)
target_link_libraries(HashTest Engine)