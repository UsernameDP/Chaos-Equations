cmake_minimum_required(VERSION 3.20)
project(OpenGL_Core)

add_library(OpenGL_Core STATIC)
target_compile_features(OpenGL_Core PRIVATE cxx_std_20)

# Vendors
option(SPDLOG_USE_STD_FORMAT ON)
target_compile_definitions(OpenGL_Core PUBLIC _SECURE_SCL=FALSE)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/imgui-docking)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/spdlog)

# Core
target_include_directories(OpenGL_Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE core_sources CONFIGURE_DEPENDS src/*.cpp)
target_sources(OpenGL_Core PRIVATE ${core_sources} "src/GLCore/Extension/Primitives/SSBO.cpp")

target_precompile_headers(OpenGL_Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp")

# Linking all libraries
target_link_libraries(OpenGL_Core PUBLIC glad glfw glm imgui spdlog opengl32)
target_link_libraries(OpenGL_Core PRIVATE project_compiler_flags)