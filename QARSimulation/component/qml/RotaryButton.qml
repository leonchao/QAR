import QtQuick 2.0

Rectangle {
    property int angle: 0
    width: 50; height: 50
    color: 'black'
    radius: width / 2
    Image {
        anchors.fill: parent
        source: 'qrc:/component/images/rotary_button.png'
        fillMode: Image.Stretch
        rotation: angle
        Behavior on rotation { RotationAnimation { duration: 300 } }
    }
}
