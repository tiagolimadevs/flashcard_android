import QtQuick 2.0



Rectangle {
	id: button
	color: "transparent"

	property var source 
	signal clicked()

	Image {
		anchors.fill: parent
		source: button.source
	}

	MouseArea {
		anchors.fill: parent
		onEntered: button.scale+=0.1
		onExited: button.scale-=0.1
		onClicked: button.clicked()
	}
}
