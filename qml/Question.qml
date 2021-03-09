import QtQuick 2.0


Rectangle {
	id: root
	color: "#FAFAFA"
	property var text: "default test a very long long text to test wrap mode"
	signal look()

	function shake() {
		shakeAnimation.start()
	}

	function clear() {
		root.text=""
	}

	Text {
		id: textQuestion
		anchors.fill: parent
		text: root.text
		font.pointSize: 20
		color: "black"
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		wrapMode: Text.WrapAnywhere
		MouseArea {
			anchors.fill: parent
			onClicked: {
				root.look()
			}
		}

		SequentialAnimation {
			id: shakeAnimation
			NumberAnimation {
				target: textQuestion
				property: "rotation"
				to: 20
				duration: 100
			}
			NumberAnimation {
				target: textQuestion
				property: "rotation"
				to: -20
				duration: 100
			}
			NumberAnimation {
				target: textQuestion
				property: "rotation"
				to: 0
				duration: 100
			}
		}
	}
}
