import QtQuick 2.0
import QtQuick.Layouts

Item {

//    default property alias children: main.children;
    default property alias data: main.data

    ColumnLayout{
        id: main
        anchors.fill: parent
    }
}

