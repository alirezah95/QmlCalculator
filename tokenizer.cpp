#include "tokenizer.hpp"

#include <iostream>

using std::cout;
using std::endl;


Tokenizer::Tokenizer()
{
	m_st_funcs = {
		{ State::Idle,      &Tokenizer::idle_hndl   },
		{ State::Int,       &Tokenizer::int_hndl    },
		{ State::Float,     &Tokenizer::float_hndl  },
		{ State::Parans,    &Tokenizer::parans_hndl },
		{ State::Operator,  &Tokenizer::oper_hndl   },
		{ State::Zsign,     &Tokenizer::zsign_hndl  },
		{ State::Symbol,	&Tokenizer::symbol_hndl },
		{ State::Letter,	&Tokenizer::letter_hndl },
		{ State::Comma,		&Tokenizer::comma_hndl	}
	};
}


void Tokenizer::get_tokens(QString s, QVector<Token>& result)
{
	m_string = s;
	m_token = "";
	m_result = &result;
	m_state = State::Idle;

	QChar input;
	while (m_string.size() > 0) {
		input = m_string[0];
		m_st_funcs[m_state](this, input);
	}
	// An extra space at the end is required to ensure that last token is
	// pushed to result too.
	m_st_funcs[m_state](this, ' ');
}


void Tokenizer::push_token_as_operator()
{
	Token token(Type::Operator, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::push_token_as_int()
{
	Token token(Type::Number, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::push_token_as_float()
{
	Token token(Type::Number, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::push_token_as_parans()
{
	if (m_token[0] == '(') {
		Token token(Type::OpenParan, m_token);
		m_result->push_back(token);
	}
	else {
		Token token(Type::CloseParan, m_token);
		m_result->push_back(token);
	}
	m_token = "";
	return;
}

void Tokenizer::push_token_as_symbol()
{
	Token token(Type::Symbol, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::push_token_as_function()
{
	Token token(Type::Function, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::push_token_as_comma()
{
	Token token(Type::Comma, m_token);
	m_result->push_back(token);
	m_token = "";
	return;
}


void Tokenizer::consume_curr_input()
{
	m_string.remove(0, 1);
	return;
}


void Tokenizer::invalid_expression()
{
	std::cout << "Invalid expr received..." << endl;
	m_string = "";
	m_token = "";
	m_state = State::Idle;
	m_result->resize(0);

	return;
}


/*
 * State handle functions.
 */
void Tokenizer::idle_hndl(QChar input)
{
	if (input.isDigit()) {
		m_token += input;
		m_state = State::Int;
	} else if (is_symbol(input)) {
		m_token += input;
		m_state = State::Symbol;
	} else if (input == '.') {
		m_token += input;
		m_state = State::Float;
	} else if (input.isLetter()) {
		m_token += input;
		m_state = State::Letter;
	} else if (is_zsign(input)) {
		m_token += input;
		m_state = State::Zsign;
	} else if (is_operator(input)) {
		m_token += input;
		m_state = State::Operator;
	} else if (is_parans(input)) {
		m_token += input;
		m_state = State::Parans;
	} else if (input.isSpace()) {
		// Stay in current state.
	} else {
		cout << "Invalid input: " << "idle" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::int_hndl(QChar input)
{
	if (input.isDigit()) {
		// Stay in current state.
		m_token += input;
	} else if (input == '.') {
		m_token += input;
		m_state = State::Float;
	} else if (input == COM_SIGN) {
		m_state = State::Comma;
		push_token_as_int();
	} else if (input.isLetter()) {
		m_state = State::Letter;
		push_token_as_int();
		m_token = QString(MUL_SIGN);
		push_token_as_operator();
		m_token += input;
	} else if (is_symbol(input)) {
		m_state = State::Symbol;
		push_token_as_int();
		m_token = QString(MUL_SIGN);
		push_token_as_operator();
		m_token += input;
	} else if (input.isSpace()) {
		m_state = State::Idle;
		push_token_as_int();
	} else if (is_operator(input)) {
		m_state = State::Operator;
		push_token_as_int();
		m_token += input;
	} else if (is_parans(input)) {
		m_state = State::Parans;
		// In order to support something like this: 2(3+4)
		if (input == '(') {
			push_token_as_int();
			m_token = QString(MUL_SIGN);
			push_token_as_operator();
		} else
			push_token_as_int();
		m_token += input;
	} else {
		cout << "Invalid input: " << "int" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::float_hndl(QChar input)
{
	if (input.isDigit()) {
		// Stay in current state.
		m_token += input;
	} else if (is_symbol(input)) {
		m_state = State::Symbol;
		push_token_as_float();
		m_token = QString(MUL_SIGN);
		push_token_as_operator();
		m_token += input;
	} else if (input == COM_SIGN) {
		m_state = State::Comma;
		push_token_as_int();
	} else if (input.isLetter()) {
		m_state = State::Letter;
		push_token_as_float();
		m_token = QString(MUL_SIGN);
		push_token_as_operator();
		m_token += input;
	} else if (input.isSpace()) {
		m_state = State::Idle;
		push_token_as_float();
	} else if (is_operator(input)) {
		m_state = State::Operator;
		push_token_as_float();
		m_token += input;
	} else if (is_parans(input)) {
		m_state = State::Parans;
		// In order to support something like this: 2.3(4+5.6)
		if (input == '(') {
			push_token_as_float();
			m_token = QString(MUL_SIGN);
			push_token_as_operator();
		} else
			push_token_as_float();
		m_token += input;
	} else {
		cout << "Invalid input: " << "float" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;

}


void Tokenizer::parans_hndl(QChar input)
{
	if (m_token == "(") {
		m_state = State::Idle;
		push_token_as_parans();
		return;
	} else if (m_token == ")") {
		if (is_operator(input)) {
			m_state = State::Operator;
			push_token_as_parans();
			m_token = input;
		} else if (is_parans(input)) {
			push_token_as_parans();
			if (input == '(') {
				m_token = QString(MUL_SIGN);
				push_token_as_operator();
			}
			m_token = input;
		} else if (input == COM_SIGN) {
			m_state = State::Comma;
			push_token_as_parans();
			m_token = input;
		} else if (input.isSpace()) {
			m_state = State::Idle;
			push_token_as_parans();
		} else {
			cout << "Invalid input: " << "parans C" << endl;
			invalid_expression();
			return;
		}
	}

	consume_curr_input();
	return;
}


void Tokenizer::oper_hndl(QChar input)
{
	if (input.isDigit()) {
		m_state = State::Int;
		push_token_as_operator();
		m_token += input;
	} else if (is_symbol(input)) {
		m_state = State::Symbol;
		push_token_as_operator();
		m_token += input;
	} else if (input == '.') {
		m_state = State::Float;
		push_token_as_operator();
		m_token += input;
	} else if (input.isLetter()) {
		m_state = State::Letter;
		push_token_as_operator();
		m_token += input;
	} else if (is_parans(input)) {
		m_state = State::Parans;
		push_token_as_operator();
		m_token += input;
	} else if (is_operator(input)) {
		push_token_as_operator();
		m_token += input;
	} else if (input.isSpace()) {
		m_state = State::Idle;
		push_token_as_operator();
	} else {
		cout << "Invalid input: " << "operator" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::zsign_hndl(QChar input)
{
	if (input.isDigit()) {
		m_state = State::Int;
		m_token += input;
	} else if (input == '.') {
		m_state = State::Float;
		m_token += input;
	} else {
		cout << "Invalid input: " << "zsign" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::symbol_hndl(QChar input)
{
	if (is_operator(input)) {
		m_state = State::Operator;
		push_token_as_symbol();
		m_token += input;
	} else if (input.isSpace()) {
		m_state = State::Idle;
		push_token_as_symbol();
	} else {
		cout << "Invalid input: " << "symbol" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::letter_hndl(QChar input)
{
	if (input.isLetterOrNumber()) {
		// Stay in current state.
		m_token += input;
	} else if (is_parans(input)) {
		m_state = State::Parans;
		push_token_as_function();
		m_token = input;
	} else {
		cout << "Invalid input: " << "letter" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}


void Tokenizer::comma_hndl(QChar input)
{
	if (input.isDigit()) {
		m_state = State::Int;
		push_token_as_comma();
		m_token += input;
	} else if (is_symbol(input)) {
		m_state = State::Symbol;
		push_token_as_comma();
		m_token += input;
	} else if (input == '.') {
		m_state = State::Float;
		push_token_as_comma();
		m_token += input;
	} else if (input.isLetter()) {
		m_state = State::Letter;
		push_token_as_comma();
		m_token += input;
	} else if (is_parans(input)) {
		m_state = State::Parans;
		push_token_as_comma();
		m_token += input;
	} else {
		cout << "Invalid input: " << "comma" << endl;
		invalid_expression();
		return;
	}
	consume_curr_input();
	return;
}
