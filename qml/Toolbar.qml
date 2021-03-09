import QtQuick 2.0
import QtQuick.Controls 2.0

ToolBar {
	id: root
       property var color: "blue"
       property var title: "default"
       property var titleColor: "white"
       signal clicked()
       Rectangle {
	       anchors.fill: parent
	       color: root.color
        }     
	Image {
		width: height
		height: parent.height*0.7
		anchors.left: parent.left
		anchors.verticalCenter: parent.verticalCenter
		source: "qrc:/images/menu"
		MouseArea {
			anchors.fill: parent
			onClicked: root.clicked()
		}
	 }
	 Label {
		 anchors.centerIn: parent
		 text: root.title
		 color: root.titleColor
		 font.pixelSize: 30
		 elide: Label.ElideRight
        }
}
