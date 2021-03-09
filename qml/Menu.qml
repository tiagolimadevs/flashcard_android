import QtQuick 2.0
import QtQuick.Controls 2.0


Drawer {
	id: root
	opacity: 0.9

	signal openFile()
	signal help()
	signal exit()

	Rectangle {
		anchors.fill: parent
		color: "#212222"
	}

	Column {
		width: parent.width
		height: parent.height
		Image {
			id: logo
			width: parent.width
			height: parent.height*0.3
			source: "qrc:/images/logo"
		}

		ListView {
			id: list
			width: parent.width
			height: parent.height*0.7
			spacing: height*0.1
			model: ["open file", "about", "exit"]
			clip: true
			
			delegate: Rectangle {
				width: parent.width
				height: list.height*0.2
				color: "transparent"
				Text {
					id: text
					anchors.centerIn: parent
					text: modelData
					font.pointSize: 25
					color: "red"
				}
				border {
					width: 0.03
					color: "red"
				}
				MouseArea {
					anchors.fill: parent
					onEntered: text.scale+=0.1
					onExited: text.scale-=0.1
					onClicked: {
						if (modelData == "open file")
							root.openFile()
						else if (modelData == "help")
								root.help()
						else
							root.exit()
					}
				}
			}
		}
	}

}
