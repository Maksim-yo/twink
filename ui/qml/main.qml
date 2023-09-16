import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Twink")
    id: main
    Loader {

        id: settingsPageLoad
    }


    Component {
        id: mainPage
        MainPage{
        }
    }

    property var temp: mainPage

    RowLayout {
        id: root
        property int leftmenu_width: 40
        anchors.fill: parent
    LeftMenu {
        id: left_menu
        Layout.preferredWidth: root.leftmenu_width
        Layout.fillHeight: true
        onWidthLayoutChanged: (w) => root.leftmenu_width = w
    }

    StackView {

        id:forward
        Layout.fillHeight: true
        Layout.fillWidth: true
        initialItem: temp
        pushEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            pushExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }
            popEnter: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 0
                    to:1
                    duration: 200
                }
            }
            popExit: Transition {
                PropertyAnimation {
                    property: "opacity"
                    from: 1
                    to:0
                    duration: 200
                }
            }

        }
    }
}
