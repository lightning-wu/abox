cmake_minimum_required(VERSION 3.8)
project(abox)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        util.h)

set(FILE_FILES
        file.cpp)

include_directories(.)

find_package(pkgconfig)
if (PKG_CONFIG_FOUND)
    message("fuck")
    pkg_check_modules(LIBFUCK libuv)
    if (LIBFUCK_FOUND)
        MESSAGE("${LIBFUCK_INCLUDE_DIRS}")
        MESSAGE("${LIBFUCK_LIBRARY_DIRS}")
        MESSAGE("${LIBFUCK_LIBRARIES}")
        include_directories(${LIBFUCK_INCLUDE_DIRS})
        link_directories(${LIBFUCK_LIBRARY_DIRS})
    else(LIBFUCK_FOUND)
        MESSAGE("what")
    endif(LIBFUCK_FOUND)
endif(PKG_CONFIG_FOUND)

add_executable(abox ${SOURCE_FILES})
target_link_libraries(abox ${LIBFUCK_LIBRARIES})

add_executable(file ${FILE_FILES})
target_link_libraries(file ${LIBFUCK_LIBRARIES})