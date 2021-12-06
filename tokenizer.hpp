#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <QtCore>
#include <map>
#include <functional>

#include "token.hpp"

enum class State{
	Idle, Int, Float, Letter, Parans, Operator, Zsign, Symbol, Comma
};


class Tokenizer
{
private:
	std::map<State, std::function<void(Tokenizer*, QChar)>>     m_st_funcs;
	QVector<Token>*												m_result;
	QString                                                     m_string;
	QString                                                     m_token;
	State                                                       m_state = State::Idle;

private:
	inline bool is_zsign(QChar i) {
		return (i == SUB_SIGN || i == SUM_SIGN);
	}
	inline bool is_operator(QChar i) {
		return (i == SUB_SIGN || i == SUM_SIGN || i == MUL_SIGN ||
				i == DIV_SIGN || i == POW_SIGN || i == SQU_SIGN ||
				i == CUB_SIGN || i == FAC_SIGN);
	}
	inline bool is_parans(QChar i) {
		return (i == '(' || i == ')');
	}
	inline bool is_symbol(QChar i) {
		return (i == PI_SIGN || i == E_SIGN);
	}

    void push_token_as_operator();
	void push_token_as_int();
	void push_token_as_float();
    void push_token_as_parans();
	void push_token_as_symbol();
	void push_token_as_function();
	void push_token_as_comma();

	void consume_curr_input();
	void invalid_expression();

	void idle_hndl      (QChar input);
	void int_hndl       (QChar input);
	void float_hndl     (QChar input);
	void parans_hndl    (QChar input);
	void oper_hndl      (QChar input);
	void zsign_hndl     (QChar input);
	void symbol_hndl	(QChar input);
	void letter_hndl	(QChar input);
	void comma_hndl		(QChar input);

public:
    Tokenizer();

	void get_tokens(QString s, QVector<Token>& result);
};

#endif // TOKENIZER_HPP
