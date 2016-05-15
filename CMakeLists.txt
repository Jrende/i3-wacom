#TODO: Create find_package for glfw, glew, glm
cmake_minimum_required (VERSION 2.6)
project (I3Wacom)

add_subdirectory(i3ipc++)

find_package(PkgConfig)
pkg_check_modules(SIGCPP REQUIRED sigc++-2.0)

#I3IPCpp_LIBRARY_DIRS
#I3IPCpp_INCLUDE_DIRS
#I3IPCpp_LIBRARIES

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -static-libgcc -static-libstdc++")
MESSAGE("I3IPCpp_INCLUDE_DIRS: ${I3IPCpp_INCLUDE_DIRS}")
MESSAGE("I3IPCpp_LIBRARY_DIRS: ${I3IPCpp_LIBRARY_DIRS}")
MESSAGE("I3IPCpp_LIBRARIES: ${I3IPCpp_LIBRARIES}")

link_directories(
  ${SIGCPP_LIBRARY_DIRS}
  3rd/jsoncpp/src/lib_json/
)

include_directories (
  ${SIGCPP_INCLUDE_DIRS}
  3rd/jsoncpp/include
  3rd/auss/include
  include/i3ipc++
  ${I3IPCpp_INCLUDE_DIRS}
)

link_directories(
  ${SIGCPP_LIBRARY_DIRS}
  3rd/jsoncpp/src/lib_json/
)

set(ALL_LIBS
  ${SIGCPP_LIBRARIES}
  ${I3IPCpp_LIBRARIES}
)

file(GLOB_RECURSE I3WACOM_SOURCES "src/*.cpp")
file(GLOB_RECURSE I3WACOM_HEADERS "src/*.h")

set (I3WACOM_INCLUDE_DIRS "")
foreach (_headerFile ${I3WACOM_HEADERS})
  get_filename_component(_dir ${_headerFile} PATH)
  list (APPEND I3WACOM_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES I3WACOM_INCLUDE_DIRS)

include_directories(
  ${I3WACOM_INCLUDE_DIRS}
)
add_executable (I3Wacom ${I3WACOM_SOURCES})
target_link_libraries(I3Wacom ${ALL_LIBS})
set_property(TARGET I3Wacom APPEND PROPERTY COMPILE_FLAGS "-O2 -Wall -Wextra -Wno-unused-parameter")
