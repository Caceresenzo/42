/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.pass.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 21:58:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 21:58:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

struct S
{
		S(int i) :
				i_(new int(i))
		{
		}

		S(const S &rhs) :
				i_(new int(*rhs.i_))
		{
		}

		S&
		operator=(const S &rhs)
		{
			*i_ = *rhs.i_;
			return *this;
		}

		~S()
		{
			delete i_;
			i_ = NULL;
		}

		bool
		operator==(const S &rhs) const
		{
			return *i_ == *rhs.i_;
		}

		int
		get() const
		{
			return *i_;
		}

		int *i_;
};

int
main(int, char**)
{
	{
		int a1[] = { 1, 2, 3, 4 };
		int a2[] = { 1, 2, 4 };

		LIST<Aware<int> > c(a1, a1 + 4);
		c.remove(3);

		ASSERT(c == LIST<Aware<int> >(a2, a2 + 3));
	}

	ASSERT_AWARE_ZERO();

	{
		int a1[] = { 1, 2, 1, 3, 5, 8, 11 };
		int a2[] = { 2, 3, 5, 8, 11 };

		LIST<Aware<int> > c(a1, a1 + 7);

		c.remove(c.front());
		ASSERT(c == LIST<Aware<int> >(a2, a2 + 5));
	}

	ASSERT_AWARE_ZERO();

	{
		int a1[] = { 1, 2, 1, 3, 5, 8, 11, 1 };
		int a2[] = { 2, 3, 5, 8, 11 };

		LIST<S> c;
		for (int *ip = a1; ip < a1 + 8; ++ip)
			c.push_back(S(*ip));
		c.remove(c.front());

		LIST<S>::const_iterator it = c.begin();
		for (int *ip = a2; ip < a2 + 5; ++ip, ++it)
		{
			ASSERT(it != c.end());
			ASSERT(*ip == it->get());
		}
		ASSERT(it == c.end());
	}

	return 0;
}
