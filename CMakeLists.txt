cmake_minimum_required(VERSION 3.10)

project(file
    VERSION 1.0.0
    DESCRIPTION "A simple and powerful library for file creation and manipulation."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h include/*.hpp)
file(GLOB_RECURSE TESTS tests/*.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set(CMAKE_CXX_WARN_DEPRECATED YES)
set(CMAKE_CXX_WARN_UNINITIALIZED YES)
set(CMAKE_CXX_WARN_UNUSED_PARAMETER YES)
set(CMAKE_CXX_WARN_UNUSED_VARIABLE YES)
set(CMAKE_CXX_WARN_UNUSED_BUT_SET_VARIABLE YES)
set(CMAKE_CXX_WARN_UNUSED_FUNCTION YES)
set(CMAKE_CXX_WARN_UNUSED_RESULT YES)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-config
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)

export(EXPORT ${PROJECT_NAME}-config
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    NAMESPACE ${PROJECT_NAME}::
)

configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}-config-install.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

enable_testing()
foreach(TEST_FILE ${TESTS})
    # Get filename without extension
    get_filename_component(TEST_NAME_RAW ${TEST_FILE} NAME_WE)
    set(TEST_NAME ${PROJECT_NAME}_${TEST_NAME_RAW}_test)

    # Create test executable
    add_executable(${TEST_NAME} ${TEST_FILE})

    # Link against required libraries
    target_link_libraries(${TEST_NAME} PRIVATE
        ${PROJECT_NAME}  # Link against main library
    )

    # Add test to CTest
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
    )

    # Set test properties
    set_target_properties(${TEST_NAME} PROPERTIES
        CXX_VISIBILITY_PRESET "default"
        BUILD_WITHOUT_DEPENDS ON
    )
endforeach()

set(CTEST_SOURCE_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR})
set(CTEST_COMMAND ${CMAKE_CTEST_COMMAND})

set(CTEST_TEST_TYPE "unit")
set(CTEST_TEST_TIMEOUT 300)
