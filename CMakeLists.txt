cmake_minimum_required(VERSION 3.2)

if (NOT "$ENV{TRAVIS_BUILD_NUMBER}" STREQUAL "")
    project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(ip_filter VERSION 0.0.1)
endif()

add_executable(ip_filter ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDART 14
    CXX_STANDART_REQUIRED ON
#    COMPILE_OPTIONS -std=gnu++14
#    COMPILE_OPTIONS -Wpedantic -Wall -Wextra -std=gnu++14
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT cowwwboy@ya.ru)

include(CPack)
