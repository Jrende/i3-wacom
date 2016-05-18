cmake_minimum_required (VERSION 3.0)
project (I3Wacom)

SET(JSONCPP_WITH_PKGCONFIG_SUPPORT OFF)
SET(JSONCPP_WITH_TESTS OFF)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
add_subdirectory(i3ipcpp)

find_package(PkgConfig)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -static-libgcc -static-libstdc++")

include_directories (
  ${SIGCPP_INCLUDE_DIRS}
  ${I3IPCpp_INCLUDE_DIRS}
)

set(ALL_LIBS
  ${SIGCPP_LIBRARIES}
  ${I3IPCpp_LIBRARIES}
)

add_executable (I3Wacom "src/main.cpp")
install(TARGETS I3Wacom DESTINATION bin)
target_link_libraries(I3Wacom ${ALL_LIBS})
set_property(TARGET I3Wacom APPEND PROPERTY COMPILE_FLAGS "-O2 -Wall -Wextra -Wno-unused-parameter")
