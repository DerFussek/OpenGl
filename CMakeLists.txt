cmake_minimum_required(VERSION 3.16)
project(OpenGlProject)

# C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Alle Quellen automatisch einsammeln
file(GLOB_RECURSE SRC_CPP CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SRC_C   CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

# Executable erzeugen
add_executable(OpenGl
    ${SRC_CPP}
    ${SRC_C}
)

# Include-Ordner
target_include_directories(OpenGl PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# GLFW-Lib-Ordner (MSVC-Version!)
target_link_directories(OpenGl PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/vc2022
)

# Bibliotheken linken
target_link_libraries(OpenGl PRIVATE
    glfw3
    opengl32
    gdi32
    user32
    shell32
)

# Runtime-Library-Konflikt (MSVC: /MDd für Debug, /MD für Release)
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Shader nach Build ins richtige Verzeichnis kopieren
add_custom_command(TARGET OpenGl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:OpenGl>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:OpenGl>/shaders
)
