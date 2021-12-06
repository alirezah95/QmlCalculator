#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <QString>
#include <iostream>

#include "math_funcs.hpp"

#define	SUM_SIGN		u'\u002b'
#define	SUB_SIGN		'-'
#define	DIV_SIGN		u'\u00f7'
#define	MUL_SIGN		u'\u00d7'
#define	POW_SIGN		u'\u005e'
#define	EQU_SIGN		u'\u003d'
#define	PER_SIGN		u'\u0025'
#define	SQU_SIGN		u'\u221a'
#define CUB_SIGN		u'\u221b'
#define	FAC_SIGN		'!'
#define PI_SIGN			u'\u03c0'
#define E_SIGN			u'\u212f'
#define COM_SIGN		','

enum class Type {
	Invalid=-1, Number, Operator, Symbol, Function, OpenParan, CloseParan,
	Comma
};

enum Operation{
	Sum, Sub, Mul, Div, Pow
};


inline QString to_string(Type t)
{
	switch (t) {
		case Type::Number:
			return "Number";
		case Type::Operator:
			return "Operator";
		case Type::Symbol:
			return "Symbol";
		case Type::Function:
			return "Function";
		case Type::OpenParan:
			return "O Paranthesis";
		case Type::CloseParan:
			return "C Paranthesis";
		case Type::Comma:
			return "Comma";
		default:
			return "";
	}
}


class Token
{
protected:
	QString		m_data;
	Type		m_type;
	u_int		m_preced;
	bool		m_r_asso = false;
	bool		m_unary = false;

public:
	Token(): m_data(""), m_type(Type::Number) {}
	Token(Type t, QString d): m_type(t), m_data(d)
	{
		if (m_type == Type::Operator) {
			if (m_data == QString(SUM_SIGN)) {
				m_preced = 1;
			} else if	(m_data == QString(SUB_SIGN)) {
				m_preced = 1;
			} else if	(m_data == QString(MUL_SIGN)) {
				m_preced = 2;
			} else if	(m_data == QString(DIV_SIGN)) {
				m_preced = 2;
			} else if	(m_data == QString(POW_SIGN)) {
				m_preced = 3;
				m_r_asso = true;
			} else if	(m_data == QString(SQU_SIGN) ||
						 m_data == QString(CUB_SIGN)) {
				m_preced = 3;
				m_r_asso = true;
				m_unary = true;
			} else if	(m_data == QString(FAC_SIGN)) {
				m_preced = 4;
				m_unary = true;
			}
		} else if (m_type == Type::Symbol) {
			m_preced = 1;
			if (m_data == QString(PI_SIGN)) {
				m_data = "3.14159265359";
			} else if (m_data == QString(E_SIGN)) {
				m_data = QString::number(exp(1));
			}
		} else if (m_type == Type::Function) {
			m_preced = 10; // function precedence is highest, like paranthesis.
		} else {
			m_preced = 0;
		}
	}

	u_int	preced()	const { return m_preced; }
	QString	data()		const { return m_data; }
	Type	type()		const { return m_type; }

	bool is_r_associative() const { return m_r_asso; }
	bool is_unary()			const { return m_unary; }

	QString string() const { return m_data + "\t\t => " + to_string(m_type); }
};

#endif // TOKEN_HPP
