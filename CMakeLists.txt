cmake_minimum_required(VERSION 3.1)
project(lyphe)

find_package(yaml-cpp REQUIRED)
find_package(SFML COMPONENTS REQUIRED window graphics )

set(SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/src/DNA.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Organism.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/OrganismHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RandomEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RenderEngine.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(${PROJECT_NAME} yaml-cpp sfml-window sfml-graphics)
