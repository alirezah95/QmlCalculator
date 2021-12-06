import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls.Material

GridLayout {
	columns: 5
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: cubSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Function
		text: "sin("
		contentText.color: Material.accent
		contentText.text: "sin"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Function
		text: "cos("
		contentText.color: Material.accent
		contentText.text: "cos"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Function
		text: "tan("
		contentText.color: Material.accent
		contentText.text: "tan"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Function
		text: "max("
		contentText.color: Material.accent
		contentText.text: "max"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: squSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: ","
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Function
		text: "log("
		contentText.color: Material.accent
		contentText.text: "log"
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "("
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: ")"
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Left column buttons
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "^"
		contentText.color: Material.accent
		contentText.text: powSign
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 2; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "^(-1)"
		contentText.color: Material.accent
		contentText.text: invSign
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 3; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "!"
		contentText.color: Material.accent
		contentText.text: facSign
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 4; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: eNumSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 5; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: piSign
		contentText.color: Material.accent
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 6; Layout.column: 0
	}
}
