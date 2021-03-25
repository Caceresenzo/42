/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_iter_iter.pass.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 18:20:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 18:20:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>
#include <vector>
#include <Vector.hpp>

template<class C, class Iterator>
	void
	test(Iterator first, Iterator last)
	{
		C c(first, last);
		ASSERT(c.size() == static_cast<std::size_t>(DISTANCE(first, last)));

		for (typename C::const_iterator i = c.begin(), e = c.end(); i != e; ++i, ++first)
			ASSERT(*i == *first);
	}

static void
basic_test_cases()
{
	Aware<int> a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 1, 0 };
	Aware<int> *an = a + sizeof(a) / sizeof(a[0]);

	test<ft::Vector<Aware<int> > >(SimpleIterator<const Aware<int>*>(a), SimpleIterator<const Aware<int>*>(an));

#if !(TEST_USE_STD)
	test<ft::Vector<Aware<int> > >(ft::Vector<Aware<int> >::iterator(a), ft::Vector<Aware<int> >::iterator(an));
	test<ft::Vector<Aware<int> > >(ft::Vector<Aware<int> >::const_iterator(a), ft::Vector<Aware<int> >::const_iterator(an));
#endif

	test<VECTOR<Aware<int> > >(a, an);
}

struct B1
{
		int x;
};

struct B2
{
		int y;
};

struct Der :
		B1,
		B2
{
		int z;
};

void
test_ctor_with_different_value_type() // Initialize a vector with a different value type.
{
	float array[3] = { 0.0f, 1.0f, 2.0f };

	{ // Make sure initialization is performed with each element value, not with a memory blob.
		VECTOR<int> v(array, array + 3);
		ASSERT(v[0] == 0);
		ASSERT(v[1] == 1);
		ASSERT(v[2] == 2);
	}

	{ // Though the types Der* and B2* are very similar, initialization still cannot be done with `memcpy`.
		Der z;
		Der *array[1] = { &z };

		VECTOR<B2*> v(array, array + 1);
		ASSERT(v[0] == &z);
	}

	{ // Though the types are different, initialization can be done with `memcpy`.
		int32_t array[1] = { -1 };
		VECTOR<unsigned int> v(array, array + 1);
		ASSERT(v[0] == 4294967295);
	}
}

int
main(void)
{
	TEST_AWARE_BLOCK(
	{
		basic_test_cases()
		;
	});

	test_ctor_with_different_value_type();

	return (0);
}
