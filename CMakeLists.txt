cmake_minimum_required(VERSION 3.7)
project(GLSLPlayground)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES "GraphicsSystem/*.cpp" "GraphicsSystem/*.h")

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Dependencies)
include_directories(${PROJECT_NAME} "Dependencies/OpenGL/include")
include_directories(${PROJECT_NAME} "Dependencies/MathExtension/include")
include_directories(${PROJECT_NAME} "Dependencies/GLFW/include")
include_directories(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} GraphicsSystem/Ui/UiComponents/UiHeader.cpp GraphicsSystem/Ui/UiComponents/UiHeader.h GraphicsSystem/Ui/UiComponents/LineGrid/Line/LineManager.cpp GraphicsSystem/Ui/UiComponents/LineGrid/Line/LineManager.h GraphicsSystem/Ui/UiComponents/LineGrid/Line/UiLine.cpp GraphicsSystem/Ui/UiComponents/LineGrid/Line/UiLine.h GraphicsSystem/Ui/UiComponents/LineGrid/Particle/ParticleManager.cpp GraphicsSystem/Ui/UiComponents/LineGrid/Particle/ParticleManager.h GraphicsSystem/Ui/UiComponents/LineGrid/Particle/Particle.cpp GraphicsSystem/Ui/UiComponents/LineGrid/Particle/Particle.h GraphicsSystem/Ui/UiComponents/UiLineGrid.cpp GraphicsSystem/Ui/UiComponents/UiLineGrid.h GraphicsSystem/Ui/UiElements/UiElement.cpp)

target_link_libraries(${PROJECT_NAME}
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/GLFW/libglfw3.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/OpenGL/OpenGL.a
        ${CMAKE_CURRENT_LIST_DIR}/Dependencies/MathExtension/MathExtension.a
        )