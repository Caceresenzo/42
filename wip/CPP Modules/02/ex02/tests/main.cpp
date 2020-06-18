#include <iostream>
#include "../Fixed.hpp"

#define LOGGING true
#define OFFSET (1 << 8)
#define xassert(exp) \
	{ \
		bool ___ok = (exp); \
		if (LOGGING && ___ok) \
			std::cout << "\e[92mPASSED\e[39m: " << #exp << std::endl; \
		if (!___ok) { \
			std::cout << "\e[91mFAILED\e[39m: " << #exp << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

int
main(void)
{
	Fixed a = Fixed(8);
	Fixed b = Fixed((float) 16.0);

	xassert(false == (a > a));
	xassert(true == (b > a));
	xassert(false == (b > b));

	xassert(false == (a < a));
	xassert(false == (b < a));
	xassert(false == (b < b));

	xassert(true == (a >= a));
	xassert(true == (b >= a));
	xassert(true == (b >= b));

	xassert(true == (a <= a));
	xassert(false == (b <= a));
	xassert(true == (b <= b));

	xassert(false == (a != a));
	xassert(true == (b != a));
	xassert(false == (b != b));

	xassert(true == (a == a));
	xassert(false == (b == a));
	xassert(true == (b == b));

	xassert(16 == (a + a).toInt());
	xassert(24 == (a + b).toInt());
	xassert(24 == (b + a).toInt());
	xassert(32 == (b + b).toInt());

	xassert(16.0 == (a + a).toFloat());
	xassert(24.0 == (a + b).toFloat());
	xassert(24.0 == (b + a).toFloat());
	xassert(32.0 == (b + b).toFloat());

	xassert(0 == (a - a).toInt());
	xassert(-8 == (a - b).toInt());
	xassert(8 == (b - a).toInt());
	xassert(0 == (b - b).toInt());

	xassert(0.0 == (a - a).toFloat());
	xassert(-8.0 == (a - b).toFloat());
	xassert(8.0 == (b - a).toFloat());
	xassert(0.0 == (b - b).toFloat());

	xassert(64 == (a * a).toInt());
	xassert(128 == (a * b).toInt());
	xassert(128 == (b * a).toInt());
	xassert(256 == (b * b).toInt());

	xassert(64.0 == (a * a).toFloat());
	xassert(128.0 == (a * b).toFloat());
	xassert(128.0 == (b * a).toFloat());
	xassert(256.0 == (b * b).toFloat());

	xassert(1 == (a / a).toInt());
	xassert(0 == (a / b).toInt());
	xassert(2 == (b / a).toInt());
	xassert(1 == (b / b).toInt());

	xassert(1.0 == (a / a).toFloat());
	xassert(0.5 == (a / b).toFloat());
	xassert(2.0 == (b / a).toFloat());
	xassert(1.0 == (b / b).toFloat());

	xassert(Fixed::min(a, b) == a);
	xassert(Fixed::max(a, b) == b);

	xassert(8.0 == (a).toFloat());
	xassert((8.0 + (1.0 / OFFSET)) == (++a).toFloat());
	xassert(8.0 == (--a).toFloat());

	xassert(16.0 == (b).toFloat());
	xassert((16.0 + (1.0 / OFFSET)) == (++b).toFloat());
	xassert((16.0 + (2.0 / OFFSET)) == (++b).toFloat());
	xassert((16.0 + (3.0 / OFFSET)) == (++b).toFloat());
	xassert((16.0 + (4.0 / OFFSET)) == (++b).toFloat());
	xassert((16.0 + (3.0 / OFFSET)) == (--b).toFloat());
	xassert((16.0 + (2.0 / OFFSET)) == (--b).toFloat());
	xassert((16.0 + (1.0 / OFFSET)) == (--b).toFloat());
	xassert(16.0 == (--b).toFloat());

	xassert(16.0 == (b++).toFloat());
	xassert((16.0 + (1.0 / OFFSET)) == (b++).toFloat());
	xassert((16.0 + (2.0 / OFFSET)) == (b++).toFloat());
	xassert((16.0 + (3.0 / OFFSET)) == (b++).toFloat());
	xassert((16.0 + (4.0 / OFFSET)) == (b--).toFloat());
	xassert((16.0 + (3.0 / OFFSET)) == (b--).toFloat());
	xassert((16.0 + (2.0 / OFFSET)) == (b--).toFloat());
	xassert((16.0 + (1.0 / OFFSET)) == (b--).toFloat());
	xassert(16.0 == (b).toFloat());

	return 0;
}
