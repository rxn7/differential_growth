cmake_minimum_required(VERSION 3.10)

project(
	differential_growth
	VERSION 1.0
	LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


file(GLOB_RECURSE PROJECT_SOURCES
	CONFIGURE_DEPENDS
	src/*.c
)

add_executable(differential_growth ${PROJECT_SOURCES})

add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
target_link_libraries(differential_growth PRIVATE SDL3::SDL3 m)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -ffast-math")

if (WIN32)
	target_compile_definitions(differential_growth PRIVATE SDL_MAIN_HANDLED)
endif()
