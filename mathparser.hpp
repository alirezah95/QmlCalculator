#ifndef MATHPARSER_HPP
#define MATHPARSER_HPP

#include <QObject>
#include <qqml.h>
#include <variant>

#include "token.hpp"


class MathParser : public QObject
{
	Q_OBJECT
	QML_ELEMENT
public:
	explicit MathParser(QObject *parent = nullptr);
	Q_INVOKABLE QString error() { return m_error; }
	Q_INVOKABLE bool evaluate(const QString& expr);
	Q_INVOKABLE	double value() { return m_value; }
private:
	void get_postfix_notation(const QString& expr, QVector<Token>& tokens,
							  QVector<Token>& result);
	double get_value(QString operation, double operand_0, double operand_1);

private:
	QString					m_error;
	float					m_value = 0.0;

};

#endif // MATHPARSER_HPP
