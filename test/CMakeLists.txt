set(BINARY ${CMAKE_PROJECT_NAME}_test)

find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cc)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME}_lib GTest::GTest GTest::Main)