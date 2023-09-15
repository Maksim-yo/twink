import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.folderlistmodel 2.1
import Qt5Compat.GraphicalEffects
import QtCore

Item {

    id: root
    property string textColorHeader: "black"
    property string textColorItem: "white"
    property string backColorItem: "black"
    property string textColorLabelItem: "black"
    property string backColor: "white"
    property int input_width: 150
    property int input_height: 100
    property alias image: img.source
    property alias isSave: root.temp
    property bool temp: false
    property var item
    property bool isImageLoaded: false
    property int index
    property int rowMargin: 15
    signal saveClicked(var map)

    signal checkIsSave();
    signal resultIsSave(bool val);

    function validate(message, input_name, index){
        return metadata_handler.onEdited(message, input_name, index);
    }

    function isAnyDataChanged(){

        if (item.name != title_input.text )
            return true;
        if (item.artist != artist_input.text)
            return true;
        if (item.album_name != album_input.text)
            return true;
        if (item.album_year != album_year_input.text)
            return true;
        if(root.isImageLoaded)
            return true;
        return false;

    }
    Connections {

        target: root
        function onSaveClicked(map){
            metadata_handler.onSaved(map)
        }
        function onCheckIsSave(){

            var res = isAnyDataChanged();
            resultIsSave(res);
        }
    }
    Rectangle {

        id: container
        color: backColor
        anchors.fill: parent

        ColumnLayout {

            anchors.fill: parent

            Rectangle {

               id: wrapper_header
               Layout.fillWidth: true
               height: 150
               color: "grey"
               Layout.alignment: Qt.AlignTop

               RowLayout {

                id: header
                anchors.fill: parent
                spacing: 15

                Item {

                    id: placeholder
                    height: 1
                    width: 10
                }

                Item{

                    Layout.preferredWidth: img.width
                    Layout.preferredHeight: img.height

                    Image {

                        id: img
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 100
                        width: 100
                        height: 100

                    }
                    Image {

                        anchors.centerIn: parent

                        id: sec_img
                        source: "qrc:/assets/download_icon.png"
                        Layout.preferredHeight: 50
                        Layout.preferredWidth: 50
                        width: 50
                        height: 50
                        opacity: 0
                    }


                    MouseArea{

                        anchors.fill: parent
                        onClicked: fileDialog.open()
                        hoverEnabled: true
                        onEntered: {
                            img.opacity = 0.3
                            sec_img.opacity = 1
                        }

                        onExited: {
                            img.opacity = 1
                            sec_img.opacity = 0
                        }
                    }
                }


                FileDialog {
                    id: fileDialog
                    currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
                    onAccepted: {
                        img.source = selectedFile
                        root.isImageLoaded = true

                    }
                }
                ColumnLayout {


                    Item {

                        width: 1
                        height: wrapper_header.height/ 2 - image.height/2
                    }

                    Text {
                        id: title
                        font.pixelSize: 26
                        font.bold: true
                        text: title_input.text
                        color: textColorHeader

                    }

                    Text {

                        id: artist
                        font.pixelSize: 20
                        text: artist_input.text
                        color: textColorHeader
                    }

                    RowLayout {


                        spacing: 5

                        Text {
                            id: _album_
                            text: "Album: "
                            font.pixelSize: 16
                            color: textColorHeader
                        }

                        Text {
                            id: album
                            text: album_input.text + ", "
                            font.pixelSize: 16
                            color: textColorHeader

                        }

                        Text {
                            id: _album_year
                            text: album_year_input.text
                            font.pixelSize: 16
                            color: textColorHeader
                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 1
                        }
                    }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 1

                    }
                }
            }


            Rectangle {

                Layout.fillWidth: true
                Layout.fillHeight: true
                height: 1

                ScrollView  {
                    anchors.fill: parent

                    contentWidth: -1

                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                GridLayout {
                    anchors.fill: parent
                    columns: 3

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                        LabelItem{

                            id: artist_input
                            width: root.input_width
                            height: root.input_height
                            text_label_color: textColorLabelItem
                            Layout.alignment: Qt.AlignCenter

                            text: root.item.artist
                            isTextDefault: root.item.artist_is_default
                            text_color: textColorItem
                            back_color: backColorItem
                            item_name: "Artist"
                            isOptional: false
                            onTextEdited: (text) => {

                                artist_input.error_message = validate(text, "artist_name", root.index)

                            }
                        }

                        LabelItem{
                            Layout.alignment: Qt.AlignCenter

                            id: title_input
                            width: root.input_width
                            height: root.input_height
                            text_label_color: textColorLabelItem
                            text: root.item.name
                            text_color: textColorItem
                            back_color:backColorItem
                            item_name: "Title"
                            isOptional: false
                            onTextEdited: (text) => {

                                title_input.error_message = validate(text, "track_title", root.index)

                            }

                        }

                        LabelItem{
                            Layout.alignment: Qt.AlignCenter

                            id: album_input
                            width: root.input_width
                            height: root.input_height
                            text_label_color: textColorLabelItem
                            text: root.item.album_name
                            isTextDefault: root.item.album_name_is_default
                            text_color: textColorItem
                            back_color:backColorItem
                            item_name: "Album"
                            isOptional: false
                            onTextEdited: (text) => {

                                album_input.error_message = validate(text, "album_name", root.index)

                            }

                        }
                        LabelItem{
                            Layout.alignment: Qt.AlignCenter

                            id: album_year_input
                            width: root.input_width
                            height: root.input_height
                            text_label_color: textColorLabelItem
                            text: root.item.album_year
                            isTextDefault: root.item.album_year_is_default
                            text_color: textColorItem
                            back_color:backColorItem
                            item_name: "Album Year"
                            isOptional: true
                            onTextEdited: (text) => {

                                album_year_input.error_message = validate(text, "album_year", root.index)

                            }
                        }

                    }
                }
            }
            Rectangle {

                id: footer
                Layout.preferredHeight: save.height + 5
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                Layout.rightMargin: 15
                Layout.bottomMargin: 15
                RowLayout {

                    id: footer_container
                    spacing: 14
                    anchors.fill: parent

                    Item {
                        Layout.preferredHeight: 1
                        Layout.fillWidth: true
                    }

                    CustomButton {
                        id: save
                        text: "Save"
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 40
                        Layout.alignment: Qt.AlignRight
                        onClicked: {

                            root.isSave = true
                            item.name = title_input.text
                            item.artist = artist_input.text
                            console.log("artist name: ")
                            console.log(item.artist)
                            console.log(artist_input.text)
                            item.album_name = album_input.text
                            item.album_year = album_year_input.text
                            if(root.isImageLoaded){
                                item.image = fileDialog.selectedFile
                            }
                            saveClicked(item.item)
                        }
                    }

                    CustomButton {
                        id: cancel
                        text: "Cancel"
                        Layout.alignment: Qt.AlignRight
                        Layout.preferredWidth: 100
                        Layout.preferredHeight: 40
                    }
                }
            }
        }
    }
}


