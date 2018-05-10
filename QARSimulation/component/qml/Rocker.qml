import QtQuick 2.0

Item {
    property int index: 8
    property int offset: 50
    Image {
        source: 'qrc:/component/images/rocker_default.png'
        fillMode: Image.Stretch
        anchors.fill: parent
        Image {
            id: hand
            anchors.fill: parent
            source: 'qrc:/component/images/hand.png'
            visible: index != 8

            Image {
                id: arrow
                property int dura: 400
                anchors { left: parent.left; leftMargin: (parent.width - arrow.width) / 2; top: parent.top; topMargin:  (parent.height - arrow.height) / 2 }
                source: 'qrc:/component/images/arrow.png'
                visible: index != 8
                rotation: (index % 9) * 45
                NumberAnimation on anchors.leftMargin {
                    from: (hand.width - arrow.width) / 2
                    to: index == 0 ? (hand.width - arrow.width) / 2 - offset : (hand.width - arrow.width) / 2 + offset
                    duration: arrow.dura
                    running: index == 0 || index == 4
                    loops: 5
                    onStopped: {
                        arrow.anchors.leftMargin = (hand.width - arrow.width) / 2
                        arrow.anchors.topMargin = (hand.height - arrow.height) / 2
                    }
                }

                NumberAnimation on anchors.topMargin {
                    from: (hand.height - arrow.height) / 2
                    to: index == 2 ? (hand.height - arrow.height) / 2 - offset : (hand.height - arrow.height) / 2 + offset
                    duration: arrow.dura
                    running: index == 2 || index == 6
                    loops: 5
                    onStopped: {
                        arrow.anchors.leftMargin = (hand.width - arrow.width) / 2
                        arrow.anchors.topMargin = (hand.height - arrow.height) / 2
                    }
                }

                ParallelAnimation {
                    running: index == 1 || index == 5
                    NumberAnimation {
                        target: arrow
                        property: "anchors.leftMargin"
                        from: (hand.width - arrow.width) / 2
                        to: index == 1 ? (hand.width - arrow.width) / 2 - offset : (hand.width - arrow.width) / 2 + offset
                        duration: arrow.dura
                    }
                    NumberAnimation {
                        target: arrow
                        property: "anchors.topMargin"
                        from: (hand.height - arrow.height) / 2
                        to: index == 1 ? (hand.height - arrow.height) / 2 - offset : (hand.height - arrow.height) / 2 + offset
                        duration: arrow.dura
                    }
                    loops: 5;
                    onStopped: {
                        arrow.anchors.leftMargin = (hand.width - arrow.width) / 2
                        arrow.anchors.topMargin = (hand.height - arrow.height) / 2
                    }
                }

                ParallelAnimation {
                    running: index == 3 || index == 7
                    NumberAnimation {
                        target: arrow
                        property: "anchors.leftMargin"
                        from: (hand.width - arrow.width) / 2
                        to: index == 3 ? (hand.width - arrow.width) / 2 + offset : (hand.width - arrow.width) / 2 - offset
                        duration: arrow.dura
                    }
                    NumberAnimation {
                        target: arrow
                        property: "anchors.topMargin"
                        from: (hand.height - arrow.height) / 2
                        to: index == 3 ? (hand.height - arrow.height) / 2 - offset : (hand.height - arrow.height) / 2 + offset
                        duration: arrow.dura
                    }
                    loops: 5;
                    onStopped: {
                        arrow.anchors.leftMargin = (hand.width - arrow.width) / 2
                        arrow.anchors.topMargin = (hand.height - arrow.height) / 2
                    }
                }
            }
        }
    }
}
