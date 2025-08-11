cmake_minimum_required(VERSION 4.0)
project(audio-fft-visualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    set(HOMEBREW_PREFIX "/opt/homebrew")
else()
    set(HOMEBREW_PREFIX "/usr/local")
endif()

set(CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(PNG REQUIRED)
find_package(glm REQUIRED)

add_library(glad STATIC
    external/glad/src/glad.c)
target_include_directories(glad PUBLIC
    external/glad/include)

file(GLOB_RECURSE PROJECT_SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    glad
    glfw
    OpenGL::GL
    PNG::PNG
    "-framework CoreAudio"
    "-framework AudioToolbox"
    "-framework AudioUnit")

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glad/include  
    ${HOMEBREW_PREFIX}/include
)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
    PNG_SKIP_SETJMP_CHECK
    PNG_DEBUG=0)
