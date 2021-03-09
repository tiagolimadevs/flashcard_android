import QtQuick 2.0


Rectangle {
	id: root
	width: parent.width
	height: parent.height
	color: "#FAFAFA"
	property int current: -1
	property var currentText: ""
	z: 10

	ListView {
		id: listview
		anchors.fill: parent
		model: widget.myList
		delegate: Rectangle {
			width: parent.width
			height: root.height/3
			color: root.current == index ? "#EBEBEB" : "#FAFAFA"
			Text {
				text: modelData
				anchors.centerIn: parent
				color: root.current == index ? "green" : "black"
			}
			MouseArea {
				anchors.fill: parent
				onClicked: {
					root.current = index
					root.currentText = modelData
				}
			}
		}
	}

}
