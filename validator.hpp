#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <QString>
#include <QVector>

#include "token.hpp"

using ValState = Type;

class Validator
{
public:
	explicit Validator();

	bool validate(const QVector<Token>& tokens);

private:
	ValState	m_state = ValState::Invalid;
};

#endif // VALIDATOR_HPP
