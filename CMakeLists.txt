# Set minimum required CMake version and project information
cmake_minimum_required(VERSION 3.0.0)
project(BobEngine
    VERSION 0.0.1
    DESCRIPTION "Game Engine"
    HOMEPAGE_URL "https://github.com/MrCatNerd/BobEngine"
    LANGUAGES CXX
)

# Binary output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/lib")

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the build typ
# set(CMAKE_BUILD_TYPE Release)
add_compile_options(-g)
add_compile_options(-Wall)


# OS specific stuff
if(WIN32) # Windows
elseif(APPLE) # Apple
else() # Linux
endif()

# Define source files
file(GLOB_RECURSE _SOURCE_FILES CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.hpp"
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Exclude files starting with underscore '_<file>'
list(FILTER _SOURCE_FILES EXCLUDE REGEX ".*\\/_.*\\..*")

# Create executable target
add_executable(${PROJECT_NAME} ${_SOURCE_FILES})

# Add packages
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${OPENGL_INCLUDE_DIR}"
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile_commands.json (you don't need this i got a thingy in the Makefile that does the same thing)

