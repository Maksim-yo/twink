import QtQuick 2.15
import QtQuick.Controls

Item {
    id: root
//    property alias  defautl_text: input.text
    property string text_color
    property string defaultTextColor: "#A9A9A9"
    property alias  back_color: back.color
    property int    border_size: 4
    property string border_color: "grey"
    property alias text: input.text
    property string text_basic
    property bool isTextDefault
    signal textEdited(var text);
//    property var validator
    function getSize(str){

        return str.length;

    }
    Component.onCompleted: root.text_basic = root.text
    Rectangle {


        id: temp

        anchors.fill: parent
        border.color: root.border_color
        border.width: root.border_size
        color: "black"
        radius: 30

        TextField {

            id: input
//            anchors.centerIn: parent
            color: root.isTextDefault ? root.defaultTextColor : root.text_color
//            text: root.text
            width: parent.width - parent.width * 1/4
            height: parent.height * 4/6
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            background: Rectangle {
                id: back
                anchors.fill: parent
            }
            onTextEdited:  {
                root.textEdited(input.text)
                if (input.color != root.text_color)
                        input.color = root.text_color
            }
            onPressed: {
                if (isTextDefault && input.text == root.text){
                    input.text = ""

                }
            }

            onEditingFinished: {
                if (isTextDefault && input.text == "") {
                    input.text = root.text_basic
                    input.color = root.defaultTextColor
                }
            }
            font.pixelSize: 16
        }
    }
}
