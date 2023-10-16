cmake_minimum_required(VERSION 3.0.0)
project(graphics VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(graphics src/main.cpp
    src/visualizer.h src/visualizer.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

project(imgui-sfml-example
  VERSION 1.0
  LANGUAGES CXX
)

add_subdirectory(dependencies)

target_link_libraries(graphics
  PUBLIC
    ImGui-SFML::ImGui-SFML
)
