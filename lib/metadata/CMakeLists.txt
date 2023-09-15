add_library(metadatalib SHARED

    include/metadata/IParser.h
    include/metadata/TagLib.h

    include/metadata/ISaver.h

    impl/ISaver.cpp
    impl/TagLib.cpp
    impl/IParser.cpp
    )

set_target_properties(metadatalib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (WIN32)
    add_custom_command(
            TARGET metadatalib POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${TAGLIB_BINARY_DIR}/taglib/tag.dll"
            ${CMAKE_CURRENT_BINARY_DIR}
            )
endif()

target_include_directories(metadatalib INTERFACE
        include
        )

target_include_directories(metadatalib PRIVATE
        include
        impl
        )


target_link_libraries(metadatalib PRIVATE taglib Qt6::Core)
target_link_libraries(metadatalib PRIVATE utils )


if(BUILD_TESTING)
        add_subdirectory(test)
endif()

install(TARGETS metadatalib  DESTINATION ${SHARED_INSTALL_DIR})
