import QtQuick 2.5 
import QtQuick.Particles 2.0 

Rectangle {
	id: root 
	color: "transparent" 
	x: -width
	visible: x!=-width
	

	property var text: "congratulations"
	property var angleAnimation: 250
	property int angleMin: 250
	property int angleMax: 290
	property int angleVariation: 1
	property int angleUp: 0

	signal clicked()

	function moveAngle() {
		if (root.angleUp) {
			root.angleAnimation += root.angleVariation
			if (root.angleAnimation >= root.angleMax) {
				root.angleUp = 0
			}
		} else {
			root.angleAnimation -= root.angleVariation
			if (root.angleAnimation <= root.angleMin) {
				root.angleUp = 1
			}
		}

	}

	Timer {
		interval: 50
		running: particleSystem.running
		repeat: true
		onTriggered: root.moveAngle()
	}


	ParallelAnimation {
		id: openAnimation
		ColorAnimation {
			target: root
			property: "color"
			from: "transparent"
			to: "black"
			duration: 500
			easing.type: Easing.OutInElastic
		}
		NumberAnimation {
			target: root
			property: "x"
			from: -root.width
			to: 0
			duration: 500
			easing.type: Easing.OutInElastic
		}
	}
	ParallelAnimation {
		id: closeAnimation
		ColorAnimation {
			target: root
			property: "color"
			from: "black"
			to: "transparent"
			duration: 500
		}
		NumberAnimation {
			target: root
			property: "x"
			from: 0
			to: -root.width
			duration: 500
		}
	}


	function start() {
		particleSystem.start()
		openAnimation.start()
	}

	function stop() {
		particleSystem.stop()
		closeAnimation.start()
	}

	MouseArea {
		anchors.fill: parent
		onClicked: root.clicked()
	}


	Text {
		id: title
		anchors.centerIn: parent
		text: root.text
		font.pointSize: parent.width/root.text.length
		opacity: 0.5
		z: 0

		SequentialAnimation {
			id: animation
			loops: Animation.Infinite
			running: particleSystem.running
			PropertyAnimation {
				target: title
				property: "color"
				to: "black"
				duration: 1000
				easing.type: Easing.InOutElastic
			}
			PropertyAnimation {
				target: title
				property: "color"
				to: "green"
				duration: 2000
				easing.type: Easing.InOutElastic
			}
			PropertyAnimation {
				target: title
				property: "color"
				to: "cyan"
				duration: 2000
				easing.type: Easing.InOutElastic
			}
			PropertyAnimation {
				target: title
				property: "color"
				to: "blue"
				duration: 2000
				easing.type: Easing.InOutElastic
			}
			PropertyAnimation {
				target: title
				property: "color"
				to: "red"
				duration: 2000
				easing.type: Easing.InOutElastic
		
			}
		}
	}
	

	ParticleSystem { 
		id: particleSystem 
		running: false

	}
	
	ImageParticle {
		id: firePainter 
		system: particleSystem
		groups: ['fire'] 
		source: "qrc:/images/fireworks"
	}

	ImageParticle {
                id: fireWorkPainter
                system: particleSystem
                groups: ['fireworks']
                source: "qrc:/images/fireworks2"
		colorVariation: 1
		alpha: 0
		rotationVariation: 90
        }

	Emitter { 
		id: firetEmitter 
		anchors {
			bottom: parent.bottom
			horizontalCenter: parent.horizontalCenter
		}
		width: root.width*0.1
		height: 1 
		z: 1
		system: particleSystem 
		group: 'fire'
		emitRate: 5
		maximumEmitted: 8
		lifeSpan: 3400
		//lifeSpanVariation: 500
		size: root.width*0.01
		endSize: 0
		velocity: AngleDirection { 
			angle: root.angleAnimation
			//angleVariation: 1
			magnitude: root.height*0.25
		} 

		acceleration: AngleDirection {
			angle: 90;
		//	angleVariation: 20
			magnitude: root.height*0.08
		} 
	}

	
	GroupGoal { 
		id: rocketChanger
		anchors.top: parent.top
		width: parent.width;
		height: parent.height*0.65
		system: particleSystem 
		groups: ['fire'] 
		goalState: 'explosion' 
		jump: true 
	}

	ParticleGroup { 
		name: 'explosion'
		system: particleSystem 
		TrailEmitter { 
			id: explosionEmitter
			anchors.fill: parent
			z: 1
			group: 'fireworks' 
			follow: 'fire'
			lifeSpan: 2000
			emitRatePerParticle: 1
			size: 1
			sizeVariation: 5
			endSize: root.width*0.20
		}
	}


	Text {
		id: textContinue
		z: 1
		height: parent.height*0.1
		anchors {
			bottom: parent.bottom
			horizontalCenter: parent.horizontalCenter
		}
		text: "click for continue..."
		color: "white"
		font.pointSize: text.length()/parent.width
		SequentialAnimation {
			loops: Animation.Infinite
			running	: animation.running
			NumberAnimation {
				target: textContinue
				property: "opacity"
				to: 100
				duration: 1000
			}
			NumberAnimation {
				target: textContinue
				property: "opacity"
				to: 0
				duration: 1000
			}
		}
	}
}
