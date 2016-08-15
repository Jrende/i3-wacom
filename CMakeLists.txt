cmake_minimum_required (VERSION 3.0)
project (i3wacom)

find_package(PkgConfig)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)

SET(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)
add_subdirectory(i3ipcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories (
  ${SIGCPP_INCLUDE_DIRS}
  ${I3IPCpp_INCLUDE_DIRS}
)

set(ALL_LIBS
  ${SIGCPP_LIBRARIES}
  ${I3IPCpp_LIBRARIES}
)

add_executable (i3wacom "src/main.cpp")
install(TARGETS i3wacom DESTINATION bin)
target_link_libraries(i3wacom ${ALL_LIBS})
set_property(TARGET i3wacom APPEND PROPERTY COMPILE_FLAGS "-O2 -Wall -Wextra -Wno-unused-parameter")
