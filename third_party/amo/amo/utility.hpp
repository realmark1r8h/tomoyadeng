#ifndef AMO_UTILITY_HPP__
#define AMO_UTILITY_HPP__



#include <amo/utility/string.hpp>
#include <amo/config.hpp>

namespace amo
{
	inline int isnan(double x) { return x != x; }
	inline int isinf(double x) { return !isnan(x) && isnan(x - x); }
}



#endif // AMO_UTILITY_HPP__