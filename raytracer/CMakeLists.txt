cmake_minimum_required(VERSION 3.20)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
# LodePNG has no release tags, so pin it to a specific commit.
FetchContent_Declare(
    lodepng
    GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
    GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

add_library(raytracer_core
    src/camera/camera.cpp
    src/colour/colour.cpp
    src/geometry/plane.cpp
    src/greeting.cpp
    src/image/image.cpp
    src/io/png_saver.cpp
    src/light/light.cpp
    src/material/flat_shader.cpp
    src/material/lambert_shader.cpp
    src/math/vector.cpp
    src/ray/ray.cpp
    src/scene/scene.cpp
    src/sphere/sphere.cpp
)
target_include_directories(raytracer_core PUBLIC include)
target_link_libraries(raytracer_core PRIVATE lodepng)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

add_custom_target(run
    COMMAND $<TARGET_FILE:raytracer>
    DEPENDS raytracer
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

include(CTest)
if(BUILD_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(raytracer_tests
        tests/camera/test_camera.cpp
        tests/colour/test_colour.cpp
        tests/geometry/test_plane.cpp
        tests/image/test_image.cpp
        tests/image/test_png_saver.cpp
        tests/light/test_light.cpp
        tests/material/test_material.cpp
        tests/material/test_lambert_shader.cpp
        tests/ray/test_ray.cpp
        tests/scene/test_scene.cpp
        tests/sphere/test_sphere.cpp
        tests/test_greeting.cpp
        tests/math/test_vector.cpp
    )
    target_link_libraries(raytracer_tests
        PRIVATE raytracer_core Catch2::Catch2WithMain lodepng
    )
    include(Catch)
    catch_discover_tests(raytracer_tests)
endif()
