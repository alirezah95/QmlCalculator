#ifndef PARSER_HPP
#define PARSER_HPP

#include <QtCore>
#include "token.hpp"


class Parser: public QObject
{
	Q_OBJECT
private:
	QString		m_error;

private:
	double get_value(QString operation, double operand_0, double operand_1);

public:
	Parser();

	QString error() { return m_error; }
	void	get_postfix_notation(const QString& expr, QVector<Token>& result);
	double	evaluate(const QString& expr);
};

#endif // PARSER_HPP
