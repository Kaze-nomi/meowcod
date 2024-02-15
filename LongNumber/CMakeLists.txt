project(LongNumber)

as_library()
#with_test(test1 gtest_main)

#single_executable(src/Main.cpp)

enable_testing()

add_executable(
  test1
  ./test/test1.cpp
)
target_link_libraries(
  test1
  GTest::gtest_main
  LongNumber
)

include(GoogleTest)
gtest_discover_tests(test1)