import QtQuick 2.0

Item {

    id: control
    property int leftValue: 0
    property int rightValue: 0
    readonly property real widthScale: width / 517
    readonly property real heightScale: height / 580
    Image {
        anchors.fill: parent
        fillMode: Image.Stretch
        source: 'qrc:/component/images/oil_background.png'
    }

    Image {
        id: left
        width: parent.width * 0.133; height: parent.height * 0.53
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (70 + (leftValue > 41 ? 120  : leftValue > 36 ? 100  : leftValue * (leftValue > 0 ? 2 : 0))) * heightScale
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -58 * widthScale
        source: 'qrc:/component/images/oil_groove.png'
        fillMode: Image.Stretch
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 300 } }
    }

    Image {
        id: block_left
        width: left.width * 1.6; height: left.height * 0.41
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (190 + (leftValue > 41 ? 190 : leftValue > 36 ? 150 : leftValue * (leftValue > 0 ? 3 : 4.3))) * heightScale
        anchors.horizontalCenter: left.horizontalCenter
        anchors.horizontalCenterOffset: -10 * left.width / 69
        fillMode: Image.Stretch
        source: 'qrc:/component/images/oil_block.png'
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 300 } }
    }


    Image {
        id: right
        width: parent.width * 0.133; height: parent.height * 0.53
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (70 + (rightValue > 41 ? 120 : rightValue > 36 ? 100 : rightValue * (rightValue > 0 ? 2 : 0))) * heightScale
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 58 * widthScale
        source: 'qrc:/component/images/oil_groove.png'
        fillMode: Image.Stretch
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 300 } }
    }

    Image {
        width: right.width * 1.6; height: right.height * 0.41
        anchors.bottom: parent.bottom
        anchors.bottomMargin: (190 + (rightValue > 41 ? 190 : rightValue > 36 ? 150 : rightValue * (rightValue > 0 ? 3 : 4.3))) * heightScale
        anchors.horizontalCenter: right.horizontalCenter
        anchors.horizontalCenterOffset: 10 * right.width / 69
        fillMode: Image.Stretch
        source: 'qrc:/component/images/oil_block.png'
        Behavior on anchors.bottomMargin { NumberAnimation { duration: 300 } }
    }
}
