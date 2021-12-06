import QtQuick 2.0
import QtQuick.Controls

Button {
	function getHoverShade() {
		return Material.theme === Material.Light ? Material.Shade300: Material.Shade700
	}
	function getPressShade() {
		return Material.theme === Material.Light ? Material.Shade400: Material.Shade600
	}

	enum Type {
		Number, Operator, Function, Control
	}

	signal buttonPressed(int type, string text)

	property int	buttonType:		CalcButton.Type.Number
	property bool	isHighlighted:	false

	Component.onCompleted: {
		buttonPressed.connect(idRoot.onButtonPressed);
	}

	hoverEnabled: true
	focusPolicy: Qt.NoFocus
	background: Rectangle {
		id: idBgRect
		anchors.fill: parent
		radius: width / 2
		color: isHighlighted ? Material.accent : Material.background
	}

	states: [
		State {
			name: ""
			PropertyChanges {
				target: idBgRect
				color: {
					return isHighlighted ? Material.accent : Material.background
				}
			}
		},
		State {
			name: "Hover"
			PropertyChanges {
				target: idBgRect
				color: {
					return Material.color(
								(isHighlighted ? accentColorNum: Material.Grey),
								getHoverShade())
				}
			}
		},
		State {
			name: "Press"
			PropertyChanges {
				target: idBgRect
				color: {
					return Material.color(
								(isHighlighted ? accentColorNum : Material.Grey),
								getPressShade())
				}
			}
		}
	]
	// Transitaions for states
	transitions: [
		Transition {
			from: "*"; to: "Hover"
			ColorAnimation { duration: 300 }
		},
		Transition {
			from: "Hover"; to: "*"
			ColorAnimation { duration: 300 }
		},
		Transition {
			from: "*"; to: ""
			ColorAnimation { duration: 300 }
		}
	]

	onHoveredChanged: {
		if (hovered)
			state = "Hover"
		else
			state = ""
	}
	onPressedChanged: {
		if (pressed)
			state = "Press"
		else if (hovered)
			state = "Hover"
		else
			state = ""
	}
	onReleased: buttonPressed(buttonType, text)
}
