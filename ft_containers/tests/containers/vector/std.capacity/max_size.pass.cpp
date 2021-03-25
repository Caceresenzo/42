/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:12:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:12:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>
#include <unit_vector.hpp>

template<typename T>
	bool
	test()
	{
		typedef VECTOR<T> C;
		typename C::size_type max = static_cast<typename C::size_type>(std::numeric_limits<typename C::size_type>::max() / sizeof(typename C::value_type));

		C c;
		return (c.max_size() <= max);
	}

int
main(void)
{
	ASSERT(test<char>());
	ASSERT(test<short>());
	ASSERT(test<int>());
	ASSERT(test<float>());
	ASSERT(test<double>());
	ASSERT(test<long>());
	ASSERT(test<long long>());
	ASSERT(test<Aware<int> >());
	ASSERT(test<std::string>());
	ASSERT(test<VECTOR<long> >());

	return (0);
}
