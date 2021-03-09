import QtQuick 2.0


Rectangle {
	id: root
	color: "#FAFAFA"
	signal verifique()

	Rectangle {
		id: verifique
		anchors.centerIn: parent
		width: parent.width*0.98
		height: parent.height*0.8
		color: "green"
		radius: height*0.1
		border.color: "darkgreen"
		Text {
			text: "verificar"
			anchors.centerIn: parent
			font.pointSize: height*0.7
			color: "white"
		}
		MouseArea {
			anchors.fill: parent
			onEntered: {
				verifique.border.width += 5
			}
			onExited: {
				verifique.border.width -= 5
			}
			onClicked: root.verifique()
		}

	}

}
