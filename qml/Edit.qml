import QtQuick 2.0


Rectangle {
	id: root
	color: "transparent"
	property alias currentText: textEdit.text

	function clearText() {
		textEdit.clear()
		textEdit.cursorVisible = true
	}


	TextInput {
		id: textEdit
		anchors {
			verticalCenter: parent.verticalCenter
			horizontalCenter: parent.horizontalCenter
		}
		width: parent.width*0.8
		height: parent.height
		font.pointSize: 25
		color: "black"
		wrapMode : Text.Wrap
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: ""
		selectByMouse: false
		cursorVisible: true
	}

}
