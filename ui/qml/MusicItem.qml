import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls

Item {

    id: root
    property string image: "qrc:/assets/unknown_image.png"
    property string artist_name: "Unknown"
    property string title_name: "Unknown"
    property string duration
    property string back_color: "transparent"
    property alias  path: trackPath.text

    Rectangle {

        id: container
        anchors.fill: parent
        color: back_color

        RowLayout {

            anchors.fill: parent
            spacing: 10

            Image {

                id: img
                source : root.image
                property int img_width: 50
                property int img_height: 50
                Layout.preferredWidth: img_width
                Layout.preferredHeight: img_height
                Layout.minimumWidth: img_width
                Layout.minimumHeight: img_height
                Layout.maximumWidth: img_width
                Layout.maximumHeight: img_height
                Layout.leftMargin: 10

            }


            ColumnLayout {

                spacing: 0
                Item {

                    Layout.preferredWidth: title.width
                    Layout.preferredHeight: title.height
                    Text {

                        id: title
                        text: title_name
                        font.pixelSize: 16
                    }
                }
                Item {

                    Layout.preferredWidth: artist.width
                    Layout.preferredHeight: artist.height

                    Text {

                        id: artist
                        text: artist_name
                        font.pixelSize: 14

                    }

                }

                Item {

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Text {

                        anchors.fill: parent
                        id: trackPath
                        elide: Text.ElideRight

                        font.pixelSize: 12
                    }
                }
            }

            Item {

                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.minimumWidth: 10
            }


            ColumnLayout {


                Text {

                    id: dur
                    Layout.rightMargin: 20
                    text: root.duration
                    font.pixelSize: 16

                }
            }


        }

    }
}
