cmake_minimum_required(VERSION 3.20)

project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(raytracer_core
    src/camera/camera.cpp
    src/colour/colour.cpp
    src/greeting.cpp
    src/math/vector.cpp
    src/ray/ray.cpp
    src/sphere/sphere.cpp
)
target_include_directories(raytracer_core PUBLIC include)

add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

add_custom_target(run
    COMMAND $<TARGET_FILE:raytracer>
    DEPENDS raytracer
    USES_TERMINAL
)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)
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
        tests/ray/test_ray.cpp
        tests/sphere/test_sphere.cpp
        tests/test_greeting.cpp
        tests/math/test_vector.cpp
    )
    target_link_libraries(raytracer_tests PRIVATE raytracer_core Catch2::Catch2WithMain)
    include(Catch)
    catch_discover_tests(raytracer_tests)
endif()
