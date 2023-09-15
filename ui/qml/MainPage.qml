import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts


Item {

    id: root
    property alias image: bar.img
    property int leftmenu_width: 40
    RowLayout {
        anchors.fill: parent
        Layout.fillWidth: true
        Layout.fillHeight: true

        ColumnLayout {

            Layout.leftMargin: 10
            Layout.topMargin: 4

            SearchBar {

                id: bar
                height: 50
                width: 350
                Layout.alignment: Qt.AlignHCenter
                img: "qrc:/assets/search.png"
            }

            Rectangle {

                color: "black"
                Layout.topMargin: 20
                Layout.preferredHeight: 4
                Layout.preferredWidth: root.width  - root.width / 6
                Layout.alignment: Qt.AlignHCenter

            }
            ColumnLayout {

                MusicList {

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }



            }
        }
    }
}
