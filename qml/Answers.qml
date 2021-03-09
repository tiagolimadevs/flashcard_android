import QtQuick 2.0


Rectangle {
	id: root
	width: parent.width
	height: parent.height
	color: "#fafafa"

	property alias current: select.current
	property alias currentText1: edit.currentText
	property alias currentText2: select.currentText
	property var type: -1

	function getRandomInt(min, max) {
		  return min+Math.floor(Math.random() * Math.floor(max));
	}

	function randomizeType() {
		edit.clearText()
		root.type = getRandomInt(1,2)
	}

	function clear() {
		root.type=-1
		select.current=-1
		edit.currentText=""
		select.currentText=""
	}


	Edit {
		id: edit
		width: parent.width
		height: parent.height*0.5
		x: visible ? 0 : -width
		visible: root.type == 1
		focus: visible
	}
	
	Select {
		id: select
		anchors.fill: parent
		visible: root.type == 2
	}
}
