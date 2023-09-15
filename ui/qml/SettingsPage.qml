import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls

Item {

    id: root
    property string parse_speed_data: ""
    property alias isSave: root.temp
    property bool temp: false

    function findElement(list, element){

        for(let i = 0; i < list.length; ++i){
            if(list[i] == element)
                return i;
        }
        return -1;
    }

    function checkingDefaultSettings(){

    if (settings.value("parsingSpeed", "Average") != parse_speed_box.currentText)
        return false;

    return true;
    }
    Rectangle {

        anchors.fill: parent
        ColumnLayout {
            anchors.fill: parent

            Rectangle {


                id: generalTitle
                Layout.preferredWidth: generalText.width
                Layout.preferredHeight: generalText.height
                Layout.topMargin: 10
                Layout.leftMargin: 16
                Text {

                 x: parent.x
                 id:generalText
                 text: "General"
                 font.pixelSize: 24

//                     Layout.leftMargin: 10
                }
            }

            Rectangle {

                id: separator
                Layout.preferredWidth: root.width - 100
                Layout.preferredHeight: 3
                color: "black"
                Layout.alignment: Qt.AlignLeft
                Layout.leftMargin: 30
            }

            Rectangle {

                Layout.preferredHeight: 33
                Layout.topMargin: 10
                Layout.leftMargin: 39
                RowLayout {
                    anchors.fill: parent
                    spacing: 15
                    Text {

                        id: parsingSpeedText
                        text: "Parsing speed"
                        font.pixelSize: 18

                    }

                    ComboBox {
                        id: parse_speed_box
                        width: 140
                        model: [ "Low", "Average", "Fast" ]
                        currentIndex: findElement(model, settings.value("parsingSpeed", "Average"))
                    }

                }
            }

            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: 1
            }

            RowLayout {
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                Layout.bottomMargin: 10
                spacing: 10
                CustomButton {
                    id: apply
                    Layout.preferredWidth: 100
                    Layout.preferredHeight: 40
                    Layout.rightMargin: 15
                    text: "apply"
                    onClicked: {
                        settings.setValue("parsingSpeed",parse_speed_box.currentText)
                        root.isSave = true
                    }
                }
            }
        }
    }
}
