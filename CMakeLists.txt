cmake_minimum_required(VERSION 3.16)
project(LeninGrad
        VERSION 1.0.0
        DESCRIPTION "A header-only C++ library for easy auto-differentiation."
        HOMEPAGE_URL "https://github.com/abhaybd/LeninGrad")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

# Testing
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.4 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_library(leningrad INTERFACE)
target_include_directories(
        leningrad
        INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(leningrad INTERFACE cxx_std_17)

add_executable(tests
        test/ArithmeticTest.cpp
        test/DerivativeTest.cpp
        test/ComparisonTest.cpp
        test/DiffOpTests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

install(TARGETS leningrad
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("LeninGradConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include/LeninGrad)
