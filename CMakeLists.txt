cmake_minimum_required(VERSION 3.3)
project(ansic)
include_directories ("/usr/local/Cellar/cmocka/1.0.1/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


add_library(cmocka STATIC IMPORTED)
set_property(TARGET cmocka PROPERTY IMPORTED_LOCATION /usr/local/Cellar/cmocka/1.0.1/lib/libcmocka.a)


set(SOURCE_FILES main.c aclist.c aclist.h acstack.h acstack.c)
add_executable(ansic ${SOURCE_FILES})
target_link_libraries (ansic cmocka)