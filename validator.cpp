#include "validator.hpp"

Validator::Validator()
{

}


bool Validator::validate(const QVector<Token>& tokens)
{
	/* Variable paran_value counts paranthesis. If an open paran is found it is
	 * incremented by 1 and if an close paran is found it is decremented by 1,
	 * at the end of the loop this value must be zero otherwise a mismatch
	 * paranthesis is occured, and along the loop paran_value should never be
	 * negative, otherwise a mismatch close paran is found.
	 */
	int paran_value = 0;
	/* Comma are only allowed in functions and a function always has a pair of
	 * paranthesis. So what we do here to ensure that every function has enough
	 * arguments for calling, is that a vector (as a stack) is defined, when
	 * a function is found a pair of two int value is pushed to that stack.
	 * First int of the pair holds paran_value when the function is found and
	 * second int is the number of commas that is needed for that function, so
	 * there is two condition:
	 * 1. Second int of the pair at top of the stack should never be negative.
	 * 2. If first int of the pair at top of the stack is zero - meaning that
	 * the last function set of paranthesis is closed - the second int of that
	 * pair should be zero.
	 * Otherwise an error in number of arguments needed for a function is
	 * occured.
	 */
	QVector<QPair<int, int> > comma_counts;
	/* Following lambdas are used to do whatever is stated for comma_counts and
	 * paran_value variables.
	 */
	auto o_paran_fnd = [&]() {
		m_state = ValState::OpenParan;
		++paran_value;
	};
	auto c_paran_fnd = [&]() {
		m_state = ValState::CloseParan;
		paran_value--;
		if (paran_value < 0) {
			// Mismatch paranthesis
			std::cout << "Mismatch paranthesis" << std::endl;
			return false;
		}
		if (comma_counts.isEmpty() == false) {
			if (comma_counts.back().first == paran_value) {
				if (comma_counts.back().second != 0) {
					std::cout << "Not enough function argument..." << std::endl;
					return false;
				} else {
					comma_counts.pop_back();
				}
			}
		}
		return true;
	};
	auto func_fnd = [&](const Token& tkn) {
		m_state = ValState::Function;
		// Save needed arguments and paran_value
		if (math_funcs.contains(tkn.data()) == false) {
			std::cout << "Function not found." << std::endl;
			return false;
		}
		comma_counts.push_back(
					{ paran_value,
					  math_funcs.constFind(tkn.data())->second - 1
					});
		return true;
	};
	auto comma_fnd = [&]() {
		m_state = ValState::Comma;
		if (comma_counts.isEmpty()) {
			std::cout << "Misplaced comma..." << std::endl;
			return false;
		}
		if (comma_counts.back().first != paran_value - 1) {
			std::cout << "Misplaced comma... 2" << std::endl;
			return false;
		}
		comma_counts.back().second--;
		if (comma_counts.back().second < 0) {
			std::cout << "Too many function arguments..." << std::endl;
			return false;
		}
		return true;
	};

	for (const auto& tkn: tokens) {
		switch (m_state) {
			case ValState::Invalid:
				switch (tkn.type()) {
					case Type::Number:
					case Type::Symbol:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Function:
						if (func_fnd(tkn) == false) return false;
						break;
					case Type::OpenParan:
						// It's ok.
						o_paran_fnd();
						break;
					case Type::Operator:
						if (tkn.data() == QString(SQU_SIGN) ||
								tkn.data() == QString(CUB_SIGN)) {
							m_state = ValState::Operator;
						} else
							return false;
						break;
					default:
						return false;
				}
				break;
			case ValState::Number:
				switch (tkn.type()) {
					case Type::Operator:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Comma:
						if (comma_fnd() == false) return false;
						break;
					case Type::CloseParan:
						// It's ok.
						if (c_paran_fnd() == false) return false;
						break;
					default:
						return false;
				}
				break;
			case ValState::Operator:
				switch (tkn.type()) {
					case Type::Number:
					case Type::Symbol:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Function:
						if (func_fnd(tkn) == false) return false;
						break;
					case Type::OpenParan:
						// It's ok.
						o_paran_fnd();
						break;
					case Type::Operator:
						if (tkn.is_unary()); // It's ok -> 2!!
						else
							return false;
						break;
					default:
						return false;
				}
				break;
			case ValState::Symbol:
				switch (tkn.type()) {
					case Type::Operator:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Comma:
						if (comma_fnd() == false) return false;
						break;
					case Type::CloseParan:
						// It's ok.
						if (c_paran_fnd() == false) return false;
						break;
					default:
						return false;
				}
				break;
			case ValState::Function:
				switch (tkn.type()) {
					case Type::OpenParan:
						// It's ok.
						o_paran_fnd();
						break;
					default:
						return false;
				}
				break;
			case ValState::OpenParan:
				switch (tkn.type()) {
					case Type::Number:
					case Type::Symbol:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Function:
						if (func_fnd(tkn) == false) return false;
						break;
					case Type::OpenParan:
						// It's ok.
						o_paran_fnd();
						break;
					case Type::Operator:
						if (tkn.is_unary() && tkn.is_r_associative()) {
							// It's ok.
							m_state = tkn.type();
						} else {
							return false;
						}
						break;
					default:
						return false;
				}
				break;
			case ValState::CloseParan:
				switch (tkn.type()) {
					case Type::Operator:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::Comma:
						if (comma_fnd() == false) return false;
						break;
					case Type::CloseParan:
						// It's ok.
						if (c_paran_fnd() == false) return false;
						break;
					default:
						return false;
				}
				break;
			case ValState::Comma:
				switch (tkn.type()) {
					case Type::Number:
					case Type::Symbol:
						// It's ok.
						m_state = tkn.type();
						break;
					case Type::OpenParan:
						// It's ok.
						o_paran_fnd();
						break;
					case Type::Function:
						if (func_fnd(tkn) == false) return false;
						break;
					default:
						return false;
				}
				break;
		}
	}

	if (paran_value != 0) {
		std::cout << "Mismatch paranthesis: 142" << std::endl;
		return false;
	}

	if (tokens.isEmpty()) {
		std::cout << "Error" << std::endl;
		return false;
	}
	const auto& last_token = tokens.back();
	switch (m_state) {
		case ValState::Number:
		case ValState::Symbol:
		case ValState::CloseParan:
			return true;
			break;
		case ValState::Operator:
			if (last_token.is_unary() && !last_token.is_r_associative())
				return true;
			else
				return false;
			break;
		default:
			return false;
	}
}
