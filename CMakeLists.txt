cmake_minimum_required(VERSION 3.10)
project(Solhem_End)

set(CMAKE_CXX_STANDARD 17)

# Set paths to local dependencies
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/External)

# GLAD
set(GLAD_INCLUDE_DIR ${EXTERNAL_DIR}/glad/include)
set(GLAD_SOURCE ${EXTERNAL_DIR}/glad/src/glad.c)

# GLFW
set(GLFW_INCLUDE_DIR ${EXTERNAL_DIR}/glfw/include)
set(GLFW_LIBRARY ${EXTERNAL_DIR}/glfw/lib-arm64/libglfw.3.dylib)

# GLM (header-only library)
set(GLM_INCLUDE_DIR ${EXTERNAL_DIR}/glm)

# Include directories
include_directories(${GLAD_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add executable
add_executable(Solhem_End main.cpp ${GLAD_SOURCE}
        src/Game.cpp
        include/Game.h
        src/Sprite.cpp
        include/Sprite.h
        src/Shader.cpp
        include/Shader.h
        src/Mesh.cpp
        include/Mesh.h
        include/Texture.h
        src/Texture.cpp
)

# Link libraries and frameworks (macOS-specific)
target_link_libraries(Solhem_End
        ${GLFW_LIBRARY}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework CoreVideo"
        "-framework IOKit"
)
# Used for loading files
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")

# Set RPATH to find the GLFW library at runtime
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${EXTERNAL_DIR}/glfw/lib")