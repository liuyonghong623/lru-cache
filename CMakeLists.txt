cmake_minimum_required(VERSION 3.16)

project(lru_cache
	VERSION 1.0.0
	LANGUAGES CXX
)

add_library(lru_cache INTERFACE)

target_include_directories(lru_cache
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(lru_cache INTERFACE cxx_std_17)

include(CTest)

if(BUILD_TESTING)

	add_executable(test_lru_cache
		tests/test_lru_cache.cpp
	)


target_link_libraries(test_lru_cache PRIVATE lru_cache)

target_compile_options(test_lru_cache PRIVATE
	-Wall
	-Wextra
	-Wpedantic
)

add_test(
	NAME lru_cache_tests
	COMMAND test_lru_cache
)

endif()
