cmake_minimum_required (VERSION 3.8)
project ("Meow")

set (CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "-O0")

# set compiler flags

# find required tools
find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)

include(cmake/Core.cmake)

add_subdirectory("LongNumber")
add_subdirectory("MeowPi")



# Google tests
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)