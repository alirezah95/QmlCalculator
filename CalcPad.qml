import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
	columns: 4

	// First row
	CalcButton {
		id: idBtnClr; buttonType: CalcButton.Type.Control
		text: "c"
		display: "IconOnly"
		icon.source: "qrc:/assets/clearall.png"
		icon.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnBack; buttonType: CalcButton.Type.Control
		text: "d"
		display: "IconOnly"
		icon.source: "qrc:/assets/clear.png"
		icon.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnPercent; buttonType: CalcButton.Type.Operator
		text: perSing
		contentText.color: Material.color(Material.Grey)
		contentText.font.pointSize: operFontSize - operFontSize * 0.2
		enabled: false
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnDiv; buttonType: CalcButton.Type.Operator
		text: divSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Second row
	CalcButton {
		id: idBtn1
		text: "1"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn2
		text: "2"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn3
		text: "3"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnMul; buttonType: CalcButton.Type.Operator
		text: mulSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Third row
	CalcButton {
		id: idBtn4
		text: "4"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn5
		text: "5"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn6
		text: "6"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnSub; buttonType: CalcButton.Type.Operator
		text: subSign
		contentText.color: Material.accent
		contentText.text: "\u2212"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Forth row
	CalcButton {
		id: idBtn7
		text: "7"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn8
		text: "8"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn9
		text: "9"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnPlus; buttonType: CalcButton.Type.Operator
		text: sumSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Fifth row
	CalcButton {
		id: idModeTglBtn; buttonType: CalcButton.Type.Control
		text: ">"
		isHighlighted: true
		contentText.font.pointSize: operFontSize - operFontSize * 0.2
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtn0
		text: "0"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnPeriod; buttonType: CalcButton.Type.Number
		text: "."
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		id: idBtnEqual; buttonType: CalcButton.Type.Operator
		text: equSign
		isHighlighted: true
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}

}
