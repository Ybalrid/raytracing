#pragma once

#include <math.h>
#include <corecrt_math_defines.h>

namespace MathTools
{
	inline bool solveQuadratic(const double& a, const double& b, const double& c, double& x0, double& x1)
	{
		//Delta = B² - 4AC
		const auto discr = b * b - 4 * a * c;

		//No real solution
		if(discr < 0)
			return false;

		//Only one real solution
		if(discr == 0)
			x0 = x1 = -0.5 * b / a;

		//Pair of real solution
		else
		{
			const auto q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
			x0			 = q / a;
			x1			 = c / q;
		}

		return true;
	}
}
