import QtQuick 2.0

Item {
    property int needleState: 0
    Image {
        anchors.centerIn: parent
        source: needleState == 0 ? 'qrc:/component/images/left_needle.png' : needleState == 1 ? 'qrc:/component/images/mid_needle.png' : 'qrc:/component/images/right_needle.png'
    }
}
