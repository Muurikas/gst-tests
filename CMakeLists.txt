cmake_minimum_required(VERSION 2.8.11)
project(gst-tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -W -Wall -pedantic")


file(GLOB sources src/*.cpp)
message(STATUS "found sources: ${sources}" )

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB_PKG REQUIRED glib-2.0)
pkg_check_modules(GST_PKG REQUIRED gstreamer-1.0)
pkg_check_modules(GOBJ_PKG REQUIRED gobject-2.0)

if(GLIB_PKG_FOUND)
    include_directories(${GLIB_PKG_INCLUDE_DIRS})
endif()

if(GST_PKG_FOUND)
    include_directories(${GST_PKG_INCLUDE_DIRS})
endif()


add_executable(gst-tests ${sources})
target_link_libraries(gst-tests gobject-2.0 glib-2.0 gstreamer-1.0)


install(TARGETS gst-tests
	RUNTIME DESTINATION /usr/bin/)

