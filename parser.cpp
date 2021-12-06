#include <iostream>
#include "parser.hpp"
#include "tokenizer.hpp"


Parser::Parser()
{

}


double Parser::get_value(QString operation, double operand_0, double operand_1)
{
	if (operation == "+") {
		return operand_0 + operand_1;
	} else if (operation == "-") {
		return operand_0 - operand_1;
	} else if (operation == "*") {
		return operand_0 * operand_1;
	} else if (operation == "/") {
		return operand_0 / operand_1;
	} else if (operation == "^") {
		return pow(operand_0, operand_1);
	} else {
		return 0.0;
	}
}


void Parser::get_postfix_notation(const QString& expr, QVector<Token>& result)
{
	Tokenizer tk;
	QVector<Token> tokens;
	tk.get_tokens(expr, tokens);
	for (auto& tk: tokens)
		std::cout << tk.string().toStdString() << std::endl;

	result.reserve(tokens.size());
	QVector<Token> opr_stack;

	while (tokens.size() > 0) {
		auto nxt_tkn = tokens[0];
		switch (nxt_tkn.type()) {
		case Type::Number:
			result.push_back(nxt_tkn);
			break;
		case Type::Operator:
			if (opr_stack.size() == 0)
				opr_stack.push_back(nxt_tkn);
			else {
				while (opr_stack.size() > 0) {
					auto top_tkn = opr_stack.back();
					if (top_tkn.type() == Type::OpenParan)
						break;
					int prc_diff = top_tkn.preced() - nxt_tkn.preced();
					if (prc_diff > 0
							|| (prc_diff == 0 && !nxt_tkn.is_r_associative())) {
						// Pop top_tkn from opr_stack and push it to result
						result.push_back(top_tkn);
						opr_stack.pop_back();
					} else
						break;
				}
				opr_stack.push_back(nxt_tkn);
			}
			break;
		case Type::OpenParan:
			if (tokens.size() > 1)
				if (tokens[1].type() == Type::CloseParan) {
					m_error = "Empty set of paranthesis.";
					result.resize(0);
					return;
				}
			opr_stack.push_back(nxt_tkn);
			break;
		case Type::CloseParan:
			if (opr_stack.size() == 0) {
				m_error = "Mismatch paranthesis.";
				result.resize(0);
				return;
			}
			auto o_paran_found = false;
			while (opr_stack.size() > 0) {
				if (opr_stack.back().type() != Type::OpenParan) {
					result.push_back(opr_stack.back());
					opr_stack.pop_back();
				} else {
					o_paran_found = true;
					opr_stack.pop_back();
					// discard nxt_tkn
					break;
				}
			}
			if (!o_paran_found) {
				m_error = "Mismatch paranthesis.";
				result.resize(0);
				return;
			}
			break;
		}
		tokens.pop_front();
	}

	while (opr_stack.size() > 0) {
		auto top_tkn = opr_stack.back();
		if (top_tkn.type() == Type::OpenParan) {
			m_error = "Mismatch paranthesis.";
			result.resize(0);
			return;
		}
		result.push_back(top_tkn);
		opr_stack.pop_back();
	}
	return;
}


double Parser::evaluate(const QString& expr)
{
	QVector<Token> result;
	get_postfix_notation(expr, result);
	if (result.size() == 0) {
		std::cout << m_error.toStdString() << std::endl;
		return 0.0;
	}

	QVector<double> eval_stack;
	while (result.size() > 0) {
		auto nxt_tkn = result.front();
		switch (nxt_tkn.type()) {
		case Type::Number:
			eval_stack.push_back(nxt_tkn.data().toDouble());
			break;
		case Type::Operator:
			auto operand_0 = eval_stack[eval_stack.size() - 2];
			auto operand_1 = eval_stack[eval_stack.size() - 1];
			eval_stack.remove(eval_stack.size() - 2, 2);
			eval_stack.push_back(get_value(nxt_tkn.data(),
										   operand_0, operand_1));
			break;

		}
		result.pop_front();
	}

	return eval_stack.front();
}
