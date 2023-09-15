cmake_minimum_required(VERSION 3.22)
project(twink VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install CACHE STRING "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ExternalProject)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Test)

if (WIN32)
set(WINDOWS_EXPORT_ALL_SYMBOLS ON)

endif()


set(TAGLIB_DESTDIR ${CMAKE_INSTALL_PREFIX}/taglib_install)
set(TAGLIB_SHARED ${CMAKE_SHARED_LIBRARY_PREFIX}tag${CMAKE_SHARED_LIBRARY_SUFFIX})
set(TAGLIB_STATIC ${CMAKE_STATIC_LIBRARY_PREFIX}tag${CMAKE_STATIC_LIBRARY_SUFFIX})

add_library(taglib SHARED IMPORTED)
message("TAGLIB_STATIC ${TAGLIB_STATIC}")
message("TAGLIB_SHARED ${TAGLIB_SHARED}")
#if (UNIX)
#    message("UNIX")
ExternalProject_Add(_taglib
    GIT_REPOSITORY https://github.com/taglib/taglib
    LIST_SEPARATOR | # Use the alternate list separator
    CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${TAGLIB_DESTDIR}
    -DWITH_ZLIB:BOOL=NO
    -DBUILD_SHARED_LIBS=ON
    BUILD_BYPRODUCTS ${TAGLIB_DESTDIR}/bin/${TAGLIB_SHARED}
    BUILD_BYPRODUCTS ${TAGLIB_DESTDIR}/lib/${TAGLIB_STATIC}
)

add_dependencies(taglib _taglib)
#endif()
#message("CMAKE_SHARED_LIBRARY_PREFIX ")
if (WIN32)
      set_target_properties(taglib PROPERTIES
          IMPORTED_LOCATION ${TAGLIB_DESTDIR}/bin/${TAGLIB_SHARED}
          INTERFACE_INCLUDE_DIRECTORIES ${TAGLIB_DESTDIR}/include
          IMPORTED_IMPLIB ${TAGLIB_DESTDIR}/lib/${TAGLIB_STATIC}
      )
else()
    set_target_properties(taglib PROPERTIES
        IMPORTED_LOCATION ${TAGLIB_DESTDIR}/lib/${TAGLIB_SHARED}
        INTERFACE_INCLUDE_DIRECTORIES ${TAGLIB_DESTDIR}/include
    )
endif()


ExternalProject_Get_Property(_taglib BINARY_DIR)
set(TAGLIB_BINARY_DIR ${BINARY_DIR})


set(SHARED_INSTALL_DIR)
if (WIN32)
    set(SHARED_INSTALL_DIR bin)
else()
    set(SHARED_INSTALL_DIR lib)
endif()

#else()
#    set_target_properties(taglib PROPERTIES
#        IMPORTED_LOCATION ${TAGLIB_DESTDIR}/lib/${TAGLIB_SHARED}
#        INTERFACE_INCLUDE_DIRECTORIES ${TAGLIB_DESTDIR}/include
#    )
#endif()
file(MAKE_DIRECTORY ${TAGLIB_DESTDIR}/include)
enable_testing()

add_subdirectory(lib)
add_subdirectory(ui)

