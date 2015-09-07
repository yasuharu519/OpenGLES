cmake_minimum_required(VERSION 2.8)

include(cmake/FindGLFW3.cmake)

set(CMAKE_VERBOSE_MAKEFILE 1)

set(PROGS
  1_clearcolor
  2_randomcolor
  3_basic_triangle
  4_draw_line
  5_draw_dots
  6_render_quad)

include_directories(/usr/local/include)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

IF(APPLE)
  find_library(COREVIDEO_LIBRARY CoreVideo)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(OpenGL_LIBRARY OpenGL)
  find_library(IOKIT_LIBRARY IOKit)
  find_library(GLFW_LIBRARY GLFW)
  SET( EXTRA_LIBS ${OpenGL_LIBRARY} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${GLFW_LIBRARY})
ENDIF(APPLE)

set(OTHER_SOURCES
  src/shader_helper.cpp)

foreach(PROG ${PROGS})
  add_executable(${PROG} main.cpp src/${PROG}.cpp ${OTHER_SOURCES})
  target_link_libraries(${PROG} ${EXTRA_LIBS})
endforeach()
