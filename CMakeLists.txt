cmake_minimum_required(VERSION 3.15)
project(csi2372_week6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

# --- Task 1: archiver ---
add_library(archiver src/archiver.cpp)
target_include_directories(archiver PUBLIC include)

add_executable(archiver_tests tests/test_archiver.cpp)
target_link_libraries(archiver_tests PRIVATE archiver)
add_test(NAME archiver_tests COMMAND $<TARGET_FILE:archiver_tests>)

# --- Task 2: build_stats ---
add_library(build_stats src/build_stats.cpp)
target_include_directories(build_stats PUBLIC include)

add_executable(build_stats_tests tests/test_build_stats.cpp)
target_link_libraries(build_stats_tests PRIVATE build_stats)
add_test(NAME build_stats_tests COMMAND $<TARGET_FILE:build_stats_tests>)

# --- Task 3: translation_cache ---
add_library(translation_cache src/translation_cache.cpp)
target_include_directories(translation_cache PUBLIC include)

add_executable(translation_cache_tests tests/test_translation_cache.cpp)
target_link_libraries(translation_cache_tests PRIVATE translation_cache)
add_test(NAME translation_cache_tests COMMAND $<TARGET_FILE:translation_cache_tests>)

# --- Task 4: snapshot ---
add_library(snapshot src/snapshot.cpp)
target_include_directories(snapshot PUBLIC include)
add_executable(snapshot_tests tests/test_snapshot.cpp)
target_link_libraries(snapshot_tests PRIVATE snapshot)
add_test(NAME snapshot_tests COMMAND $<TARGET_FILE:snapshot_tests>)