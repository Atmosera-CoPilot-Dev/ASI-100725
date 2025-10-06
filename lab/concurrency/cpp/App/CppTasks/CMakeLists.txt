cmake_minimum_required(VERSION 3.18)
project(CppTasks LANGUAGES CXX)

# Project configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_TESTING "Build unit tests" ON)

include(FetchContent)
if(BUILD_TESTING)
    # Fetch doctest first so target is available before defining tests executable
    FetchContent_Declare(
            doctest
            GIT_REPOSITORY https://github.com/doctest/doctest.git
            GIT_TAG v2.4.11
    )
    FetchContent_MakeAvailable(doctest)
endif()

add_library(tasks_lib
    src/TradeDay.cpp
    src/TradeDayProcessor.cpp
)

target_include_directories(tasks_lib PUBLIC include)

add_executable(cpp_tasks_app src/main.cpp)
target_link_libraries(cpp_tasks_app PRIVATE tasks_lib)
if (MINGW)
    # Statically link gcc & stdc++ for the main app to avoid potential runtime DLL mismatch
    target_link_options(cpp_tasks_app PRIVATE -static-libgcc -static-libstdc++)
endif()

if(BUILD_TESTING)
    enable_testing()
    add_executable(tests
        tests/test_tradedayprocessor.cpp
    )
        target_include_directories(tests PRIVATE include third_party/doctest)
        # Ensure fetched doctest headers are visible even without linking target
        if (doctest_SOURCE_DIR)
            target_include_directories(tests PRIVATE ${doctest_SOURCE_DIR})
        endif()
        # doctest is header-only; avoid linking if causing loader issues
        target_link_libraries(tests PRIVATE tasks_lib)
        # On MinGW the test executable previously failed with 0xc0000139 (entry point not found)
        # due to dynamic runtime resolution issues. Statically link libgcc & libstdc++ for tests.
        if (MINGW)
            message(STATUS "Applying MinGW static link options for tests target")
            target_link_options(tests PRIVATE -static-libgcc -static-libstdc++)
        endif()
    target_compile_definitions(tests PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
    add_test(NAME tasks_tests COMMAND tests)

    # Minimal sanity executable to isolate loader issues if needed
    add_executable(sanity tests/sanity.cpp)
    target_link_libraries(sanity PRIVATE tasks_lib)
    add_test(NAME sanity_run COMMAND sanity)
endif()
