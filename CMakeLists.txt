cmake_minimum_required(VERSION 3.29)
project(Dispatcher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE PROJECT_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
)


include(local_config.cmake OPTIONAL)

find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
        src/ui/Scenes/Rating.cpp
        src/ui/Scenes/Rating.h)

target_link_libraries(Dispatcher sfml-graphics sfml-audio)
# file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})