cmake_minimum_required(VERSION 3.20)

project(OpenGL
    VERSION 1.0
    DESCRIPTION "OpenGL Physics Engine"
    LANGUAGES C CXX)

# C++-Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Alle .cpp-Dateien einsammeln
file(GLOB_RECURSE PHYSICS_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# GLAD aus Source bauen
add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c"
)

target_include_directories(glad
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)

# Engine als Library
add_library(physics_engine STATIC
    ${PHYSICS_ENGINE_SOURCES}
)

target_include_directories(physics_engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/GLFW/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external"
)

add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/vc2022/glfw3.lib"
)

target_link_libraries(physics_engine
    PUBLIC
        glad
        glfw3
        opengl32
)


# --- Executable bauen (deine App) ---
add_executable(physics_app WIN32
    src/main.cpp
)

target_link_libraries(physics_app
    PRIVATE
        physics_engine    # hängt bereits an glad, glfw3.lib, opengl32
)