qt6_add_resources(QT_RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)

qt_add_executable(twinkapp

    main.cpp

    include/ui/ImageObject.h
    include/ui/MusicObject.h
    include/ui/Settings.h
    include/ui/SettingsPageHandler.h
    include/ui/MetadataPageHandler.h
    include/ui/Search.h
    include/ui/ParsingHandler.h
    impl/ParsingHandler.cpp
    impl/Search.cpp
    impl/MetadataPageHandler.cpp
    impl/SettingsPageHandler.cpp
    impl/Settings.cpp
    impl/ImageObject.cpp
    impl/MusicObject.cpp

    ${QT_RESOURCES}
)

qt_add_qml_module(twinkapp
    URI twink
    VERSION 1.0
    QML_FILES
    qml/LabelItem.qml
    qml/main.qml
    qml/MainPage.qml
    qml/MetadataItem.qml
    qml/MusicItem.qml
    qml/MusicList.qml
    qml/SearchBar.qml
    qml/TextInputItem.qml
    qml/LeftMenu.qml
    qml/MetadataPage.qml
    qml/CustomButton.qml
    qml/ImageButton.qml
    qml/LeftMenuItem.qml
    qml/SettingsPage.qml
    MetadataCreation.js
    )

set(UNKNOWN_IMAGE_PATH ${CMAKE_SOURCE_DIR}/assets/unknown_image.png)

configure_file (cmake_data.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/ui/cmake_data.h)
target_include_directories(twinkapp PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/include/
)

target_link_libraries(twinkapp PRIVATE utils metadatalib Qt6::Quick Qt6::Widgets)
install(TARGETS twinkapp DESTINATION bin)
