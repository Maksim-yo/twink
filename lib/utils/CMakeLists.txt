add_library(utils STATIC
    impl/ImagePNG.cpp
    impl/Image.cpp
    impl/String.cpp
    impl/Log.cpp
    impl/Utils.cpp
    impl/QtLogger.cpp

    include/utils/QtLogger.h
    include/utils/String.h
    include/utils/Image.h
    include/utils/ImagePNG.h
    include/utils/Services.h
    include/utils/Utils.h
    include/utils/Log.h

)
#set_target_properties(utils PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

#set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/test/")

#configure_file (cmake_data.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/utils/cmake_data.h)


target_include_directories(utils INTERFACE
        include
#        ${CMAKE_CURRENT_BINARY_DIR}/include/
        )

target_include_directories(utils PRIVATE
        include
        impl
        )

target_link_libraries(utils PRIVATE Qt6::Gui Qt6::Core)

set(BUILD_TESTING ON)

if(BUILD_TESTING)
        add_subdirectory(test)
endif()

install(TARGETS utils DESTINATION ${SHARED_INSTALL_DIR})

