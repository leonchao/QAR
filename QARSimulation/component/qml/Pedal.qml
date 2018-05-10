import QtQuick 2.0
import QtQuick.Controls 1.4


Item {
    id: rectangle
    property int sliderValue: 60
    readonly property int center: 70 * height / 270
    property int direction: 2

    Image {
        anchors.fill: parent
        source: 'qrc:/component/images/footbottom.png'
        fillMode: Image.Stretch
        Foot {
            id: left
            width: parent.width * 0.31; height: parent.height * 0.47
            anchors { left: parent.left; top: parent.top; topMargin: direction == 2 ? center : direction == 0 ? center - sliderValue  * height / 270 : center + sliderValue * height / 270 }
            source: 'qrc:/component/images/foot.png'
            tipImage: 'qrc:/component/images/foot_left.png'
            showTip: direction == 0
        }
        Foot {
            id: right
            width: parent.width * 0.31; height: parent.height * 0.47
            anchors { right: parent.right; top: parent.top; topMargin: direction == 2 ? center : direction == 1 ? center - sliderValue * height / 270 : center + sliderValue * height / 270 }
            source: 'qrc:/component/images/foot.png'
            tipImage: 'qrc:/component/images/foot_right.png'
            showTip: direction == 1
        }
    }
}

