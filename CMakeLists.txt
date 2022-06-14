cmake_minimum_required(VERSION 3.16)
project(LeninGrad)

set(CMAKE_CXX_STANDARD 17)

add_executable(playground test/playground.cpp)

# Testing
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.4 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        test/ArithmeticTest.cpp
        test/DerivativeTest.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
