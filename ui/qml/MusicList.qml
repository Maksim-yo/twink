import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls
import QtQml
import "../MetadataCreation.js" as MetadataPage
Item {


    id: root
    property int elemnt_height: 60
    property string backHoverColor: "grey"
    property bool isModelEmpty: true

    Connections {

        target: trackList
        function onModelUpdate() {


            if (trackList.rowCount() > 0)
                root.isModelEmpty = false
            else
                root.isModelEmpty = true
        }
    }
    function makeTooltipInfo(obj){

        var str = "";
        str += "Album: " + obj.album_name + ", " + obj.album_year + "\n";
        str += "Path: " + obj.path;
        return str;
    }
    ScrollView  {
        anchors.fill: parent

        contentWidth: -1

        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

    ColumnLayout {
        anchors.fill: parent
        id: lat
        Loader {
            id :test
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: childrenRect.width

            Layout.preferredHeight: isModelEmpty ? root.height: 0
            sourceComponent : no_data_message
            active: isModelEmpty ? true : false
        }

        Component {
            id: no_data_message

            Rectangle {

                implicitWidth: isModelEmpty ? root.width: 0

                implicitHeight: isModelEmpty ? root.height: 0
                Text {
                    anchors.centerIn: parent
                    color: "grey"
                    font.pixelSize: isModelEmpty ? 50 : 0
                    text: "Not found"
                }
            }
        }
        Repeater {

            model: trackList
            delegate: MusicItem {
                id: temp
                Layout.preferredHeight: elemnt_height
                Layout.fillWidth: true
                artist_name: model.artist
                title_name: model.name
                duration: model.duration
                path: model.path
                visible: model.visible
                image: "data:image/png;base64," + model.image.base64
                ToolTip {
                     id: toolTip
                     font.pixelSize: 11
                 }
                Timer {
                    id: timer
                    interval: 1200; running: false; repeat: false
                    onTriggered: mouse.setTooltip()



                }
                MouseArea {

                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    id: mouse
                    anchors.fill: parent
                    hoverEnabled: true
                    signal setTooltip();

                    onSetTooltip: {
                        toolTip.x = mouseX;
                        toolTip.y = mouseY;
                        toolTip.show(makeTooltipInfo(model))
                    }
                    onEntered: {

                        timer.start()
                        temp.back_color= backHoverColor
                    }

                    onMouseXChanged:  {

                        toolTip.hide()
                        timer.start()

                    }

                    onMouseYChanged: {

                        toolTip.hide()
                        timer.start()


                    }
                    onExited: {

                        timer.stop()
                        temp.back_color = "transparent"
                        toolTip.hide();

                    }
//
                    onClicked: {
                        temp.back_color= backHoverColor
                        toolTip.hide()
                        timer.stop()

                        if (mouse.button === Qt.LeftButton) {

                            var item = forward.push("MetadataPage.qml",
                                                              {
                                                              "image":temp.image,
                                                              "item":model,
                                                              "index":index})
                            left_menu.checkIsSave.connect(item.checkIsSave);
                            item.resultIsSave.connect(left_menu.resultIsSave)
                            }

                        }
                    }
                }
            }
        }
    }
}
