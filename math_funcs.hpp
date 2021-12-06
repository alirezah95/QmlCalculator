#ifndef MATH_FUNCS_HPP
#define MATH_FUNCS_HPP

#include <QtCore>


using Func = std::function<float(std::initializer_list<float>)>;
using FuncPair = QPair<Func, int>;


// Sin, Cos and Tan functions in math header needs to be override to be able
// to handle radian an degrees input.
namespace MathFunc {
// For now it is assumed that only degree values are meant
static float sin(std::initializer_list<float> l)
{
	return ::sin(*l.begin() * M_PI / 180.0L);
}

static float cos(std::initializer_list<float> l)
{
	return ::cos(*l.begin() * M_PI / 180.0);
}

static float tan(std::initializer_list<float> l)
{
	return ::tan(*l.begin() * M_PI / 180.0);
}

static float log(std::initializer_list<float> l)
{
	return ::log10f(*l.begin());
}

static float max(std::initializer_list<float> l)
{
	return fmax(*l.begin(), *(l.begin() + 1));
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
