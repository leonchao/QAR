import QtQuick 2.0

Image {
    property alias tipImage: foot.source
    property bool showTip: false
    fillMode: Image.Stretch
    Behavior on anchors.topMargin { NumberAnimation {id: animation; duration: 300 } }
    Image {
        id: foot
        anchors.fill: parent
        cache: false
        width: 256; height: 256
        fillMode: Image.Stretch
        visible: animation.running && showTip
    }
}
