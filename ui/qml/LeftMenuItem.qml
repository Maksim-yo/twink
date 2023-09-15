import QtQuick 2.0
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {

    id: root

    property string color: "white"
    property string text
    property alias src: imgBtn.src
    property alias state: wrapper.state
    property double default_bright: 0
    signal clicked()
    Rectangle {
        anchors.fill: parent
        id: wrapper
        color: root.color
        RowLayout {


            anchors.fill: parent
            spacing: 0
            ImageButton {
                id: imgBtn
                Layout.alignment: Qt.AlignCenter
                Layout.preferredHeight: 25
                Layout.preferredWidth: 25
                default_bright: root.default_bright
            }

            Text {

                id: btnText
                text: ""
                font.pixelSize: 0
                font.bold: true

                BrightnessContrast {
                    id: myBright
                    anchors.fill: parent
                    brightness: root.default_bright
                    source: btnText

                }
            }

            Item {

                id: placeholder
                Layout.preferredHeight: 1
                Layout.fillWidth: false

            }
        }
        states: [
            State {
                name: "shrink"
                PropertyChanges { target: imgBtn;  Layout.alignment: Qt.AlignLeft; Layout.leftMargin: 10;}
                PropertyChanges { target: btnText; font.pixelSize: 16; text: root.text; Layout.leftMargin: 10}
                        PropertyChanges { target: placeholder; Layout.fillWidth: true }

            }
        ]

        MouseArea {

            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                imgBtn.hoverEnter()
                if(default_bright == 0) {
                    myBright.brightness= 0.5}
//                console.log(root.)

            }
            onExited:  {
                imgBtn.hoverExit()
                myBright.brightness = default_bright

            }

            onClicked: {
                root.clicked()
            }
        }



    }
}
