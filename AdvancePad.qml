import QtQuick 2.0
import QtQuick.Layouts
import QtQuick.Controls.Material

GridLayout {
	columns: 5
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: cubSign
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "sin("
		contentItem: Text {
			text: parent.text.substring(0, parent.text.length - 1)
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "cos("
		contentItem: Text {
			text: parent.text.substring(0, parent.text.length - 1)
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "tan("
		contentItem: Text {
			text: parent.text.substring(0, parent.text.length - 1)
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "max("
		contentItem: Text {
			text: parent.text.substring(0, parent.text.length - 1)
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: squSign
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: ","
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "A"
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "("
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: ")"
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
	}
	// Left column buttons
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "^"
		contentItem: Text { text: powSign
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 2; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "^(-1)"
		contentItem: Text { text: invSign
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 3; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: "!"
		contentItem: Text { text: facSign
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 4; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: eNumSign
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 5; Layout.column: 0
	}
	CalcButton {
		buttonType: CalcButton.Type.Operator
		text: piSign
		contentItem: Text { text: parent.text
			color: Material.accent; font.pointSize: operFontSize;
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter}
		Layout.preferredWidth: itemsWidth; Layout.preferredHeight: itemsHeight
		Layout.alignment: Qt.AlignHCenter
		Layout.row: 6; Layout.column: 0
	}
}
