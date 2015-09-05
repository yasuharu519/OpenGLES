cmake_minimum_required(VERSION 2.8)

include(cmake/FindGLFW3.cmake)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(PROGS 1_clearcolor
          2_randomcolor)

include_directories(/usr/local/include)

IF(APPLE)
  find_library(COREVIDEO_LIBRARY CoreVideo)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKIT_LIBRARY IOKit)
  find_library(GLFW_LIBRARY GLFW)
  SET( EXTRA_LIBS ${OpenGL_LIBRARY} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${GLFW_LIBRARY})
ENDIF(APPLE)

foreach(PROG ${PROGS})
  add_executable(${PROG} main.cpp src/${PROG}.cpp)
  target_link_libraries(${PROG} ${EXTRA_LIBS})
endforeach()
