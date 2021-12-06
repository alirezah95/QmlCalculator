#include "mathparser.hpp"
#include "tokenizer.hpp"
#include "validator.hpp"

#include <iostream>
#include <cmath>
#include <exception>



MathParser::MathParser(QObject *parent) : QObject(parent)
{
}


float MathParser::get_value(QString operation, float operand_0,
							 float operand_1)
{
	if (operation == QString(SUM_SIGN)) {
		return operand_0 + operand_1;
	} else if (operation == QString(SUB_SIGN)) {
		return operand_0 - operand_1;
	} else if (operation == QString(MUL_SIGN)) {
		return operand_0 * operand_1;
	} else if (operation == QString(DIV_SIGN)) {
		return operand_0 / operand_1;
	} else if (operation == QString(POW_SIGN)) {
		return pow(operand_0, operand_1);
	} else if (operation == QString(SQU_SIGN)) {
		return sqrt(operand_0);
	} else if (operation == QString(CUB_SIGN)) {
		return pow(operand_0, 1.0/3.0);
	} else if (operation == QString(FAC_SIGN)) {
		return tgamma(operand_0 + 1);
	} else {
		return 0.0;
	}
}


void MathParser::get_postfix_notation(const QString& expr, QVector<Token>& tokens,
									  QVector<Token>& result)
{
	result.reserve(tokens.size());
	QVector<Token> opr_stack;

	while (tokens.size() > 0) {
		auto nxt_tkn = tokens[0];
		switch (nxt_tkn.type()) {
			case Type::Number:
			case Type::Symbol:
				result.push_back(nxt_tkn);
				break;
			case Type::Operator:
				if (opr_stack.size() == 0)
					opr_stack.push_back(nxt_tkn);
				else if (nxt_tkn.is_unary() && !nxt_tkn.is_r_associative()) {
					// Like factorial
					result.push_back(nxt_tkn);
				}
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
			case Type::Function:
				opr_stack.push_back(nxt_tkn);
				break;
			case Type::OpenParan:
				opr_stack.push_back(nxt_tkn);
				break;
			case Type::CloseParan: {
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
					} else if (opr_stack.back().type() == Type::Function) {
						result.push_back(opr_stack.back());
						opr_stack.pop_back();
					}
					break;
				}
			case Type::Comma: {
					/* In this case, pop every operator on the operator stack
					 * and push it on the result stack, until an o paran is
					 * found (there is definitly an open paran) - don't touch
					 * open paran - and discard comma.
					 */
					while (opr_stack.back().type() != Type::OpenParan) {
						result.push_back(opr_stack.back());
						opr_stack.pop_back();
					}
					break;
				}
		}
		tokens.pop_front();
	}

	while (opr_stack.size() > 0) {
		result.push_back(opr_stack.back());
		opr_stack.pop_back();
	}
	return;
}


bool MathParser::evaluate(const QString& expr)
{
	// To evaluate (parse) an expression we take three step. First the
	// expression is tokenized, then it is validated and if there was no error
	// so far, it is evaluated.
	QVector<Token> result;
	QVector<Token> tokens;

	auto tk = new Tokenizer;
	tk->get_tokens(expr, tokens);
	delete tk;
	if (tokens.isEmpty()) {
		std::cout << "Tokenizer returned with error..." << std::endl;
		return false;
	}

	Validator val;
	if (val.validate(tokens) == false) {
		std::cout << "Error: Validate returned false..." << std::endl;
		return false;
	}

	get_postfix_notation(expr, tokens, result);
	for (auto& tk: result)
		std::cout << tk.string().toStdString() << std::endl;


	if (result.size() == 0) {
		std::cout << m_error.toStdString() << std::endl;
		m_value = 0;
		return false;
	}

	QVector<float> eval_stack;
	while (result.size() > 0) {
		auto nxt_tkn = result.front();
		switch (nxt_tkn.type()) {
			case Type::Number:
			case Type::Symbol:
				eval_stack.push_back(nxt_tkn.data().toDouble());
				break;
			case Type::Operator:
				if (nxt_tkn.is_unary()) {
					auto operand = eval_stack.back();
					eval_stack.remove(eval_stack.size() - 1, 1);
					eval_stack.push_back(get_value(nxt_tkn.data(), operand, 0));
				} else {
					auto operand_0 = eval_stack[eval_stack.size() - 2];
					auto operand_1 = eval_stack[eval_stack.size() - 1];
					eval_stack.remove(eval_stack.size() - 2, 2);
					eval_stack.push_back(get_value(nxt_tkn.data(),
												   operand_0, operand_1));
				}
				break;
			case Type::Function:
				if (math_funcs.contains(nxt_tkn.data()) == false) {
					m_error = "Function doesn't exits: " + nxt_tkn.data();
					m_value = 0;
					return false;
				}
				auto fn = math_funcs[nxt_tkn.data()];
				if (fn.second == 1) {
					// Function needs one argument
					if (eval_stack.size() < 1) {
						m_error = "Malformed expression. " + to_string(nxt_tkn.type());
						m_value = 0;
						return false;
					}
					auto operand = eval_stack.back();
					eval_stack.remove(eval_stack.size() - 1, 1);
					eval_stack.push_back(fn.first({ operand }));
				} else if (fn.second == 2) {
					// Function needs two argument
					if (eval_stack.size() < 2) {
						m_error = "Malformed expression. " + to_string(nxt_tkn.type());
						m_value = 0;
						return false;
					}
					auto operand_0 = eval_stack[eval_stack.size() - 2];
					auto operand_1 = eval_stack[eval_stack.size() - 1];
					eval_stack.remove(eval_stack.size() - 2, 2);
					eval_stack.push_back(fn.first({ operand_0, operand_1 }));
				}
				break;
		}
		result.pop_front();
	}

	if (eval_stack.size() == 1) {
		m_value = QString::number(eval_stack.front());
	} else {
		m_value = "0";
		m_error = "Malformed expression, empty eval_stack";
		return false;
	}

	return true;
}

