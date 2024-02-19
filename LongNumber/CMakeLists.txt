project(LongNumber)

as_library()
#with_test(meowtest gtest_main)

#single_executable(src/Main.cpp)

enable_testing()

add_executable(
  meowtest
  ./test/meowtest.cpp
)
target_link_libraries(
  meowtest
  GTest::gtest_main
  LongNumber
)

include(GoogleTest)
gtest_discover_tests(meowtest)