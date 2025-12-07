cmake_minimum_required(VERSION 3.20)

project(OpenGL
    VERSION 1.0
    DESCRIPTION "OpenGL Physics Engine"
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------
# FreeType einbinden (aus Source)
# --------------------------------
set(FREETYPE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/freetype-2.14.1")

# FreeType mit eigenem Build-Dir ins Projekt holen
add_subdirectory(
    "${FREETYPE_ROOT}"
    "${CMAKE_BINARY_DIR}/freetype_build"
)

# --------------------------------
# Engine-Quellen
# --------------------------------
file(GLOB_RECURSE PHYSICS_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# GLAD aus Source
add_library(glad STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c"
)

target_include_directories(glad
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)

# GLFW importierte Lib
add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/vc2022/glfw3.lib"
)

# --------------------------------
# Engine-Library
# --------------------------------
add_library(physics_engine STATIC
    ${PHYSICS_ENGINE_SOURCES}
)

target_include_directories(physics_engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/GLFW/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external"
        "${FREETYPE_ROOT}/include"       # Sicherheitshalber explizit
)

target_link_libraries(physics_engine
    PUBLIC
        glad
        glfw3
        opengl32
        freetype                       # Target aus FreeType-CMake
)

# --------------------------------
# Executable
# --------------------------------
add_executable(physics_app
    src/main.cpp
)

target_link_libraries(physics_app
    PRIVATE
        physics_engine
)
