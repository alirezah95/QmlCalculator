import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import mathparser 1.0

ApplicationWindow {
	id: idRoot
	width: 450
	height: 800
	visible: true
	title: qsTr("Qml Calculator")

	readonly property string sumSign:	"\u002b"
	readonly property string subSign:	"-"
	readonly property string divSign:	"\u00f7"
	readonly property string mulSign:	"\u00d7"
	readonly property string powSign:	"\u03f0\u02b8"
	readonly property string equSign:	"\u003d"
	readonly property string perSing:	"\u0025"
	readonly property string piSign:	"\u03c0"
	readonly property string invSign:	"\u00b9\u2044\u2093"
	readonly property string squSign:	"\u221a"
	readonly property string cubSign:	"\u221b"
	readonly property string eNumSign:	"\u212f"
	readonly property string facSign:	"\u03f0!"
	readonly property string infSign:	"\u221e"

	property real	itemsWidth:		Math.min(width / 8.0, height / 12.0)
	property real	itemsHeight:	itemsWidth
	property color	itemsColor:		"azure"
	property color	fgColor:		Material.foreground
	property int	accentColorNum:	Material.DeepOrange
	property int	operFontSize:	25
	property int	numFontSize:	20
	property bool	resultState:	false

	function onButtonPressed(buttonType, txt) {
		if (resultState) {
			idCalcText.text = "";
			resultState = false;
		}

		switch (buttonType) {
		case CalcButton.Type.Number:
		case CalcButton.Type.Function:
			idCalcText.text += txt;
			break;
		case CalcButton.Type.Operator:
			if (txt === equSign){
				resultState = true;
				idCalcPrevText.text = idCalcText.text
				// Calulate the result of expression
				if (MathParser.evaluate(idCalcText.text)) {
					let val = MathParser.value();
					if (val === "-inf") {
						val = subSign + infSign;
					} else if (val === "inf") {
						val = sumSign + infSign;
					}
					idCalcText.text = val;
				} else {
					idCalcText.text = "Error";
				}
			} else {
				idCalcText.text += txt;
			}
			break;
		case CalcButton.Type.Control:
			if (txt === "d") {
				idCalcText.text = idCalcText.text.slice(0, -1);
			} else if (txt === "c") {
				idCalcText.text = "";
			} else if (txt === ">") {
				if (idStateItem.state === "Simple")
					idStateItem.state = "Advanced";
				else
					idStateItem.state = "Simple";
			}
			break;
		default:
			print("Undifined");
		}
	}

	FontLoader {
		id: idMainFont
		source: "qrc:/assets/DejaVuSans.ttf"
	}

	Material.accent: Material.color(accentColorNum)

	Component.onCompleted: idStateItem.state = "Advanced";

	Item {
		id: idStateItem

		states: [
			State {
				name: "Simple"
				PropertyChanges {
					target: idCalcPad;
					Layout.preferredWidth: idRoot.width
				}
				PropertyChanges {
					target: idAdvPad;
					anchors.leftMargin: -idRoot.width
					anchors.rightMargin: idRoot.width
				}
				PropertyChanges {
					target: idLabelsCol
					anchors.bottom: idItemsCol.top
				}
			},
			State {
				name: "Advanced"
				PropertyChanges { target: idCalcPad
					Layout.preferredWidth: idRoot.width - idRoot.width / 5.0
				}
				PropertyChanges { target: idAdvPad;
					anchors.leftMargin: 0
					anchors.rightMargin: 0
				}
				PropertyChanges {
					target: idLabelsCol; anchors.bottom: idAdvPad.top
				}
			}

		]

		transitions: [
			Transition {
				from: "Simple"; to: "Advanced"
				PropertyAnimation {
					properties: "Layout.preferredWidth, anchors.leftMargin, anchors.rightMargin"
					duration: 200
				}
				PropertyAnimation {
					property: "anchors.bottom"; duration: 1
				}
			},
			Transition {
				from: "Advanced"; to: "Simple"
				PropertyAnimation {
					properties: "Layout.preferredWidth, anchors.leftMargin, anchors.rightMargin, anchors.bottom"
					duration: 200
				}
			}
		]
	}

	ColumnLayout {
		id: idLabelsCol
		anchors {
			bottom: idItemsCol.top
			bottomMargin: 10
			left: parent.left
			right: parent.right
			leftMargin: itemsWidth / 3.0
			rightMargin: itemsWidth / 3.0
		}
		Label {
			id: idCalcPrevText
			Layout.preferredHeight: itemsHeight
			Layout.fillWidth: true

			horizontalAlignment: Qt.AlignLeft
			verticalAlignment: Qt.AlignVCenter
			textFormat: Text.PlainText
			opacity: 0.7
//			color: "silver"
			font {
				pointSize: numFontSize - numFontSize * 0.25
			}
		}

		Label {
			id: idCalcText
			Layout.preferredHeight: itemsHeight
			Layout.fillWidth: true

			horizontalAlignment: Qt.AlignLeft
			verticalAlignment: Qt.AlignVCenter
			textFormat: Text.PlainText
			font {
				pointSize: numFontSize
			}
			background: Rectangle {
				color: "gray"
				opacity: 0.2
			}

			Rectangle {
				id: idCTextBtmLine
				width: parent.width
				height: 2
				anchors.bottom: parent.bottom
				anchors.horizontalCenter: parent.horizontalCenter
				color: Material.accent
			}
		}
	}

	AdvancePad {
		id: idAdvPad
		anchors {
			left: parent.left
			right: parent.right
			leftMargin: -idRoot.width
			rightMargin: idRoot.width
			bottom: idItemsCol.bottom
		}
	}

	ColumnLayout {
		id: idItemsCol
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 20
		anchors.right: parent.right
		spacing: 10


		CalcPad {
			id: idCalcPad
			Layout.preferredWidth: idRoot.width
		}

	}
}
