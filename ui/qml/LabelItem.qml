import QtQuick 2.15
import QtQuick.Layouts

Item {

    id: root
    property alias text_color: input.text_color
    property alias item_name: item.text
    property alias  back_color: input.back_color
    property alias  border_size: input.border_size
    property alias  border_color: input.border_color
    property alias text_label_color: item.color
    property alias text: input.text
    property bool isOptional: true
    property bool isChangeable: true
    property string  error_message: ""
    property bool isTextDefault
    signal textEdited(var text);
    ColumnLayout {

        id: temp
        anchors.fill: parent
        spacing: 0

            RowLayout {
                Layout.leftMargin: 7
                spacing: 6
                id: test
                Text {

                    id: item
                    color: text_label_color
                    font.pixelSize: 18
                    font.bold: true
                }

                Text {

                    text: (isOptional == true) ? "" : "*"
                    font.pixelSize: 20
                    font.bold: true
                    height: 20
                    color: "red"
                }
            }

        Text {

            id: err_message
            text: root.error_message
            font.pixelSize: 12
            color: "red"
        }

        TextInputItem {

            id: input

            Layout.topMargin: 10
            Layout.fillWidth: true;
            Layout.fillHeight: true;

            Layout.preferredHeight: root.height - container.height - placeholder.height
            onTextEdited: (text) => root.textEdited(text)
            isTextDefault: root.isTextDefault
            border_color: root.error_message == "" ? "grey" : "red"
        }
    }
}
