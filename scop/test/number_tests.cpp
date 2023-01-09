/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_tests.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 19:39:34 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/28 19:39:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cassert>
#include <lang/Number.hpp>

# define TRY(code, message_) \
	try \
	{ \
		code; \
	} \
	catch (Exception &exception) \
	{ \
		std::cout << exception.message() << std::endl; \
		assert(exception.message() == message_); \
	}

int
main()
{
	/* integer */ {
		/* normal */ {
			assert(Number::parse<int>("0") == 0);
			assert(Number::parse<int>("1") == 1);
			assert(Number::parse<int>("-1") == -1);
		}

		/* limits */ {
			assert(Number::parse<int>("2147483647") == 2147483647);
			assert(Number::parse<int>("-2147483648") == -2147483648);

			assert(Number::parse<long>("9223372036854775807") == std::numeric_limits<long>::max());
			assert(Number::parse<long>("-9223372036854775808") == std::numeric_limits<long>::min());
		}

		/* limits */ {
			TRY(Number::parse<char>("-129"), "-129 < -128 (type's minimum)");
			TRY(Number::parse<char>("128"), "128 > 127 (type's maximum)");

			TRY(Number::parse<int>("a"), "char `a` is not in the alphabet: `0123456789`");
			TRY(Number::parse<int>("1a"), "char `a` is not in the alphabet: `0123456789`");
		}

		/* alphabet */ {
			TRY(Number::parse<int>("1", ""), "alphabet's length <= 1");
		}
	}

	/* decimal */ {
		/* normal */ {
			assert(Number::parse<float>("0") == 0.0);
			assert(Number::parse<float>("0.0") == 0.0);
			assert(Number::parse<float>("1") == 1.0);
			assert(Number::parse<float>("1.0") == 1.0);
			assert(Number::parse<float>("-1") == -1.0);
			assert(Number::parse<float>("-1.0") == -1.0);
		}
	}
}
