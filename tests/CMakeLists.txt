include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Build test binary
add_executable(my_tests test_lexer.cpp)

# Link against your library + gtest
target_link_libraries(my_tests PRIVATE compiler GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_tests)

