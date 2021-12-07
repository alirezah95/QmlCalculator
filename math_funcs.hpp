#ifndef MATH_FUNCS_HPP
#define MATH_FUNCS_HPP

#include <QtCore>


using Func = std::function<double(std::initializer_list<double>)>;
using FuncPair = QPair<Func, int>;


// Sin, Cos and Tan functions in math header needs to be override to be able
// to handle radian an degrees input.
namespace MathFunc {
// For now it is assumed that only degree values are meant
static double sin(std::initializer_list<double> l)
{
	return ::sin(*l.begin() / 180.0 * M_PI);
}

static double cos(std::initializer_list<double> l)
{
	return ::cos(*l.begin() / 180.0 * M_PI);
}

static double tan(std::initializer_list<double> l)
{
	return ::tan(*l.begin() / 180.0 * M_PI);
}

static double log(std::initializer_list<double> l)
{
	return ::log10(*l.begin());
}

static double max(std::initializer_list<double> l)
{
	return qMax(*l.begin(), *(l.begin() + 1));
}

}


static QMap<QString, FuncPair> math_funcs = {
	{ "sin", { &MathFunc::sin, 1 } },
	{ "cos", { &MathFunc::cos, 1 } },
	{ "tan", { &MathFunc::tan, 1 } },
	{ "max", { &MathFunc::max, 2 } },
	{ "log", { &MathFunc::log, 1 } }
};

#endif // MATH_FUNCS_HPP
