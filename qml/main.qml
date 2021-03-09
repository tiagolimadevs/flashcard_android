import QtQuick 2.0

Rectangle {
	id: main
	width: widget.getSize().width
	height: widget.getSize().height
	color: "#FAFAFA"

	signal win()
	property var lenSplit: 0

	onWin: {
		question.clear()
		answer.clear()
		winAnimation.start()
		
	}

	WinAnimation {
		id: winAnimation
		width: main.width
		height: main.height
		z: 100
		onClicked: {
			winAnimation.stop()
			menu.open()
			answer.x=0
		}
	}


	

	Menu {
		id: menu
		width: main.width*0.8
		height: main.height
		
		onOpenFile: {
			menu.close()
			widget.openFile()
		}
		onExit: {
			menu.close()
			Qt.quit()
			widget.close()
		}
	}

	Rectangle {
		anchors.fill: parent
		color: "#FAFAFA"
		
		Column {
			anchors.fill: parent

			Toolbar {
				id: toolbar
				width: parent.width
				height: parent.height*0.07
				color: "#FAFAFA"
				titleColor: "black"
				title: "flash card"
				onClicked: menu.open()
			}
		
			ProgressBar {
				id: progressBar
				width: parent.width
				height: parent.height*0.01
				firstColor: "#EBEBEB"
				secondColor: "green"
				thirdColor: "#778899"
				lenSplit: main.lenSplit
				px: widget.currentPx
				anchors.top: toolbar.bottom
			}

			Question {
				id: question
				text: widget.question
				width: parent.width
				height: parent.height*0.3
				anchors.top: progressBar.bottom
				
				onLook: {
					widget.lookQuestion()
				}
			}
			
			Answers {
				id: answer
				objectName: "answer"
				anchors.top: question.bottom
				width: parent.width
				height: parent.height*0.40
				clip: true 
			}

			Form {
				anchors {
					bottom: parent.bottom
					bottomMargin: height*0.3
				}

				width: parent.width
				height: parent.height*0.1
				onVerifique: {
					if (answer.type == -1 
 					|| (answer.type != 1 && answer.current == -1))
						return;
					var a = answer.type == 1 ? answer.currentText1 : answer.currentText2
					answer.current=-1
					if (a == "")
						return;


					if (a == "debug: animation") {
						main.win()
						answer.randomizeType()
					} else if (widget.verifique(a)) {
						widget.nextQuestion()
						answer.randomizeType()
					} else
						question.shake()
				}
			}
		}
	}
}
