cmake_minimum_required(VERSION 3.12)

if("$ENV{TRAVIS_TAG}" AND "$ENV{TRAVIS_BUILD_NUMBER}")
  set(PROJECT_VERSION "$ENV{TRAVIS_TAG}.$ENV{TRAVIS_BUILD_NUMBER}")
elseif("$ENV{TRAVIS_BUILD_NUMBER}")
  set(PROJECT_VERSION "0.0.$ENV{TRAVIS_BUILD_NUMBER}")
else()
  set(PROJECT_VERSION "0.0.1")
endif()

project(ip_filter VERSION "${PROJECT_VERSION}")

add_executable(ip_filter ip_filter.cpp)
add_library(lib lib.cpp)

set_target_properties(ip_filter lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}" "${CMAKE_PARENT_DIR}"
)

target_link_libraries(ip_filter PRIVATE
  lib
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT aturubar@gmail.com)

include(CPack)
