import QtQuick 2.0

Rectangle {
	id: root
	
	property var firstColor: "white"
	property var secondColor: "green"
	property var thirdColor: "black"
	property int lenSplit: 1
	property int px: 0

	color: firstColor

	NumberAnimation on lenSplit {
		duration: 1000
	}

	Rectangle {
		id: progress
		height: root.height
		width: (root.width/100)*root.px
		color: root.secondColor
	}

	Repeater {
		model: root.lenSplit

		delegate: Rectangle {
			x: ((index+1)*(root.width/root.lenSplit))-width
			height: root.height
			width: root.height*0.2
			color: root.thirdColor
			visible: progress.width >= x
		}
	}

	
	

}
