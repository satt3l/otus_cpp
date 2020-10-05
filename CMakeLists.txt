cmake_minimum_required(VERSION 3.12)

if("$ENV{TRAVIS_TAG}" AND "$ENV{TRAVIS_BUILD_NUMBER}")
  set(PROJECT_VERSION "$ENV{TRAVIS_TAG}.$ENV{TRAVIS_BUILD_NUMBER}")
elseif("$ENV{TRAVIS_BUILD_NUMBER}")
  set(PROJECT_VERSION "0.0.$ENV{TRAVIS_BUILD_NUMBER}")
else()
  set(PROJECT_VERSION "0.0.1")
endif()

project(hellow VERSION "${PROJECT_VERSION}")
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
configure_file(version.h.in version.h)

add_executable(hellow hellow.cpp)
add_library(lib lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(hellow lib test_version PROPERTIES
  CXX_STANDARD_14
  CXX_STANDARD_REQUIRED_ON
)

set_target_properties(test_version PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(lib
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(hellow PRIVATE
  lib
)

target_link_libraries(test_version PRIVATE
  ${Boost_LIBRARIES}
  lib
)

install(TARGETS hellow RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT aturubar@gmail.com)

include(CPack)
enable_testing()
add_test(test_version test_version)
