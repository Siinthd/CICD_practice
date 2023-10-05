cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

find_package(GTest REQUIRED)
configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version test_version.cpp)

set_target_properties(
	helloworld_cli helloworld test_version PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
	)
target_include_directories(helloworld
	PRIVATE "${CMAKE_BINARY_DIR}"
	)
set_target_properties(test_version PROPERTIES
	INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
	)
target_link_libraries(helloworld_cli PRIVATE
	helloworld
	)
target_link_libraries(test_version
#	${GTEST_LIBRARIES}
	helloworld
	GTest::gtest_main
	)
install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT razelim@list.ru)

include(CPack)

enable_testing()
include(GoogleTest)
gtest_discover_tests(test_version)

