cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.1.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})

add_executable(ip_filter main.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
