import QtQuick 2.0
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Item {

    id: root
    property alias img: image.source
    property int img_width: 20
    property int img_height: 20


   Rectangle {

        id: bar
        anchors.fill: parent
        border.color: "white"
        border.width: 2
        radius: 20
        color: "#4d4d4d"

        Row {

            anchors.fill: parent

            Item {
                id: placeholder
                height: 1
                width: 15
            }

            Image {

                id: image
                y: bar.height/2 - image.height/2
                width: 20
                height: 20

                BrightnessContrast {
                    id:myBright
                    anchors.fill: parent
                    source: image
                }
            }


            Item {
                id: temp
                height: root.height
                width: bar.width - (placeholder.width + image.width )  - 12

                TextField {

                    id: input
                    width: parent.width - 20
                    height: parent.height - 20
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    background: Rectangle {
                        id: input_back
                        anchors.fill: parent
                        color: "white" }
                    onTextEdited: {
                        searchHandler.edit(input.text)
                    }
                    color: "black"
                    font.pixelSize: 16
                }

            }

        }


        MouseArea{

            anchors.fill: parent
            hoverEnabled: true
            onClicked: mouse.accepted = false
            onPressed: mouse.accepted = false
            onReleased: mouse.accepted = false
            onPositionChanged: mouse.accepted = false
            onDoubleClicked: mouse.accepted = false
            onPressAndHold: mouse.accepted = false
            onEntered: {

                bar.color = "#595959"
                input_back.color = "white"
                bar.border.color = "#595959"
                myBright.brightness = 0.3
    //            trackList.add()

            }

            onExited: {

                bar.color = "#4d4d4d"
    //            input_back.color = "#4d4d4d"
                bar.border.color = "white"
                myBright.brightness = 0

            }
        }
   }

}
