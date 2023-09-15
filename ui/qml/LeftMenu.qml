import QtQuick 2.4
import QtQuick.Layouts 1.1
import QtQuick.Controls
import Qt.labs.platform


Item {

    id: root
    property string color: "#787878"
    property bool is_shrink: false
    property int to_shrink_width: 100
    property string state: ""
    property bool isPopupDialogNeeded: false
    signal widthLayoutChanged(int width)
    signal click(string name)
    signal checkIsSave()
    signal resultIsSave(var bool)
    function checkStackElemnt(element, checkingElement){

        var res = element.includes(checkingElement);
        return res;

    }

    MessageDialog {
        id: dialog
        buttons: MessageDialog.Ok | MessageDialog.Cancel
        text: "Are you sure you want to exit without save?"
        title: "Alert"
        onAccepted: forward.pop()


    }

    Component {

        id: homePage
        MainPage {
        }
    }
    Component {

        id: settingsTemp

        SettingsPage {

        }
    }
    Connections {
        target: root

        //shrink
        function onWidthLayoutChanged(w){


            if(is_shrink == true){

                root.state = "shrink"
            }
            else {

                root.state = ""
            }
        }


        function onResultIsSave(val){

            isPopupDialogNeeded = val;
        }
    }


    Rectangle {

        id: wrapper
        anchors.fill: parent
        color: root.color

        ColumnLayout {

            id: temp1
            anchors.fill: parent
            spacing: 10

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                color:"white"

                ColumnLayout {
                    anchors.fill: parent
                    id: menuButtons
                    ImageButton {

                        id: menuBtn
                        Layout.topMargin: 7
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 25
                        src: "qrc:/assets/more.png"
                        onClicked: {
                            if (!is_shrink){
                                root.width = wrapper.width + to_shrink_width
                                is_shrink = true
                            }
                            else {
                                root.width = wrapper.width - to_shrink_width
                                is_shrink = false
                            }
                            widthLayoutChanged(root.width)
                        }
                    }




                    LeftMenuItem {

                        id: homeBtn
                        src: "qrc:/assets/home.png"
                        text: "Home"
                        color: root.color
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        state: root.state
                        onClicked: {
                            if (!checkStackElemnt(forward.currentItem.toString(), "MainPage")) {

                                forward.push(forward.initialItem)
                            }
                        }
                    }

                    LeftMenuItem {

                        id: settingsBtn
                        src: "qrc:/assets/settings.png"
                        text: "Settings"
                        color: root.color
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        state: root.state
                        onClicked: {
                            if (!checkStackElemnt(forward.currentItem.toString(), "SettingsPage")) {
                                forward.push(settingsTemp)
                                root.click("settingsBtn")
                            }
                        }

                    }

                    LeftMenuItem {

                        id: folderBtn
                        src: "qrc:/assets/folder.png"
                        text: "Folder"
                        color: root.color
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        state: root.state
                        onClicked: {
                            console.log(forward.currentItem.toString())
                            if (checkStackElemnt(forward.currentItem.toString(), "MainPage")) {
                                fileDialog.open()
                            }
                        }

                        FolderDialog {
                            id: fileDialog
                            currentFolder: StandardPaths.standardLocations(StandardPaths.MusicLocation)[0]
                            onAccepted: parsingHandler.changedPath(currentFolder)
                        }

                    }
                }

            }


            Item {
                id: temp
                Layout.preferredWidth: 1
                Layout.fillHeight: true
            }

            LeftMenuItem {

                id: backBtn
                src: "qrc:/assets/back.png"
                Layout.alignment: Qt.AlignHCenter
                text: "Back"
                color: root.color
                implicitHeight: 30
                Layout.fillWidth: true
                state: root.state
                onClicked: {
                    if (checkStackElemnt(forward.currentItem.toString(), "MetadataPage") || checkStackElemnt(forward.currentItem.toString(), "SettingsPage")) {

                        checkIsSave();
                        if (isPopupDialogNeeded)
                            dialog.open();
                        else
                            forward.pop()
                    }
                    else if (forward.depth > 1){
                        forward.pop()
                    }
                }
            }

        }
    }
}
