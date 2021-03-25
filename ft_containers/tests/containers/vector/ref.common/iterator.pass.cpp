/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.pass.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:35:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:35:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	typedef Aware<std::string> Aw;
	typedef VECTOR<Aw> Vec;
	typedef Vec::iterator Iter;
	typedef Vec::const_iterator CIter;
	typedef Vec::reverse_iterator RIter;
	typedef Vec::const_reverse_iterator CRIter;

	{
		Vec v(1, Aw("42"));

		Iter a;

		ASSERT(a.base() == NULL);

		Iter b(v.begin());
		ASSERT(b.base() == v.begin().base());

		b = a;
		ASSERT(a.base() == b.base());

		ASSERT(a == b);

		a = v.begin();
		ASSERT(a != b);

		ASSERT(*a == Aw("42"));

		ASSERT(a->x() == Aw("42").x());

		*a = Aw("43");
		ASSERT(*a == Aw("43"));

		a = v.begin();
		ASSERT(++a == v.end());

		a = v.begin();
		ASSERT((a++) == v.begin());
		ASSERT(a == v.end());

		a = v.begin();
		*a++ = Aw("44");
		ASSERT(v.front() == Aw("44").x());
		ASSERT(a == v.end());

		a = v.end();
		ASSERT(--a == v.begin());

		a = v.end();
		ASSERT((a--) == v.end());
		ASSERT(a == v.begin());

		a = v.end() - 1;
		*a-- = Aw("45");
		ASSERT(v.back() == Aw("45").x());
		ASSERT(a == v.begin() - 1);

		a = v.begin();
		ASSERT(a + 1 == v.end());
		ASSERT(v.begin() + 1 == v.end());

		a = v.begin();
		ASSERT(1 + a == v.end());
		ASSERT(1 + v.begin() == v.end());

		a = v.end();
		ASSERT(a - 1 == v.begin());

		a = v.end();
		b = v.begin();
		ASSERT(a - b == 1);
		ASSERT(v.end() - v.begin() == 1);

		a = v.end();
		b = v.begin();
		ASSERT(a > b);
		ASSERT(v.end() > v.begin());

		a = v.begin();
		b = v.end();
		ASSERT(a < b);
		ASSERT(v.begin() < v.end());

		a = v.begin();
		b = v.begin();
		ASSERT(a >= b);
		ASSERT(v.begin() >= v.begin());
		ASSERT(v.end() >= v.begin());
		ASSERT(v.end() >= v.end());

		a = v.begin();
		b = v.begin();
		ASSERT(a <= b);
		ASSERT(v.begin() <= v.begin());
		ASSERT(v.begin() <= v.end());
		ASSERT(v.end() <= v.end());

		a = v.begin();
		ASSERT((a += 1) == v.end());

		a = v.end();
		ASSERT((a -= 1) == v.begin());

		a = v.begin();
		a[0] = Aw("46");
		ASSERT(a[0] == Aw("46"));

		a = v.end();
		ASSERT(a[-1] == Aw("46"));
	}

	{
		const Vec v(1, Aw("42"));

		CIter a;

		ASSERT(a.base() == NULL);

		CIter b(v.begin());
		ASSERT(b.base() == v.begin().base());

		b = a;
		ASSERT(a.base() == b.base());

		ASSERT(a == b);

		a = v.begin();
		ASSERT(a != b);

		ASSERT(*a == Aw("42"));

		ASSERT(a->x() == Aw("42").x());

		a = v.begin();
		ASSERT(++a == v.end());

		a = v.begin();
		ASSERT((a++) == v.begin());
		ASSERT(a == v.end());

		a = v.end();
		ASSERT(--a == v.begin());

		a = v.end();
		ASSERT((a--) == v.end());
		ASSERT(a == v.begin());

		a = v.begin();
		ASSERT(a + 1 == v.end());
		ASSERT(v.begin() + 1 == v.end());

		a = v.begin();
		ASSERT(1 + a == v.end());
		ASSERT(1 + v.begin() == v.end());

		a = v.end();
		ASSERT(a - 1 == v.begin());

		a = v.end();
		b = v.begin();
		ASSERT(a - b == 1);
		ASSERT(v.end() - v.begin() == 1);

		a = v.end();
		b = v.begin();
		ASSERT(a > b);
		ASSERT(v.end() > v.begin());

		a = v.begin();
		b = v.end();
		ASSERT(a < b);
		ASSERT(v.begin() < v.end());

		a = v.begin();
		b = v.begin();
		ASSERT(a >= b);
		ASSERT(v.begin() >= v.begin());
		ASSERT(v.end() >= v.begin());
		ASSERT(v.end() >= v.end());

		a = v.begin();
		b = v.begin();
		ASSERT(a <= b);
		ASSERT(v.begin() <= v.begin());
		ASSERT(v.begin() <= v.end());
		ASSERT(v.end() <= v.end());

		a = v.begin();
		ASSERT((a += 1) == v.end());

		a = v.end();
		ASSERT((a -= 1) == v.begin());

		a = v.begin();
		ASSERT(a[0] == Aw("42"));

		a = v.end();
		ASSERT(a[-1] == Aw("42"));
	}

	{
		Vec v(1, Aw("42"));

		RIter a;
		RIter b(v.rbegin());
		ASSERT(b.base() == v.rbegin().base());

		b = a;
		ASSERT(a.base() == b.base());

		ASSERT(a == b);

		a = v.rbegin();
		ASSERT(a != b);

		ASSERT(*a == Aw("42"));

		ASSERT(a->x() == Aw("42").x());

		*a = Aw("43");
		ASSERT(*a == Aw("43"));

		a = v.rbegin();
		ASSERT(++a == v.rend());

		a = v.rbegin();
		ASSERT((a++) == v.rbegin());
		ASSERT(a == v.rend());

		a = v.rbegin();
		*a++ = Aw("44");
		ASSERT(v.front() == Aw("44").x());
		ASSERT(a == v.rend());

		a = v.rend();
		ASSERT(--a == v.rbegin());

		a = v.rend();
		ASSERT((a--) == v.rend());
		ASSERT(a == v.rbegin());

		a = v.rend() - 1;
		*a-- = Aw("45");
		ASSERT(v.back() == Aw("45").x());
		ASSERT(a == v.rbegin() - 1);

		a = v.rbegin();
		ASSERT(a + 1 == v.rend());
		ASSERT(v.rbegin() + 1 == v.rend());

		a = v.rbegin();
		ASSERT(1 + a == v.rend());
		ASSERT(1 + v.rbegin() == v.rend());

		a = v.rend();
		ASSERT(a - 1 == v.rbegin());

		a = v.rend();
		b = v.rbegin();
		ASSERT(a - b == 1);
		ASSERT(v.rend() - v.rbegin() == 1);

		a = v.rend();
		b = v.rbegin();
		ASSERT(a > b);
		ASSERT(v.rend() > v.rbegin());

		a = v.rbegin();
		b = v.rend();
		ASSERT(a < b);
		ASSERT(v.rbegin() < v.rend());

		a = v.rbegin();
		b = v.rbegin();
		ASSERT(a >= b);
		ASSERT(v.rbegin() >= v.rbegin());
		ASSERT(v.rend() >= v.rbegin());
		ASSERT(v.rend() >= v.rend());

		a = v.rbegin();
		b = v.rbegin();
		ASSERT(a <= b);
		ASSERT(v.rbegin() <= v.rbegin());
		ASSERT(v.rbegin() <= v.rend());
		ASSERT(v.rend() <= v.rend());

		a = v.rbegin();
		ASSERT((a += 1) == v.rend());

		a = v.rend();
		ASSERT((a -= 1) == v.rbegin());

		a = v.rbegin();
		a[0] = Aw("46");
		ASSERT(a[0] == Aw("46"));

		a = v.rend();
		ASSERT(a[-1] == Aw("46"));
	}

	{
		const Vec v(1, Aw("42"));

		CRIter a;
		CRIter b(v.rbegin());
		ASSERT(b.base() == v.rbegin().base());

		b = a;
		ASSERT(a.base() == b.base());

		ASSERT(a == b);

		a = v.rbegin();
		ASSERT(a != b);

		ASSERT(*a == Aw("42"));

		ASSERT(a->x() == Aw("42").x());

		a = v.rbegin();
		ASSERT(++a == v.rend());

		a = v.rbegin();
		ASSERT((a++) == v.rbegin());
		ASSERT(a == v.rend());

		a = v.rend();
		ASSERT(--a == v.rbegin());

		a = v.rend();
		ASSERT((a--) == v.rend());
		ASSERT(a == v.rbegin());

		a = v.rbegin();
		ASSERT(a + 1 == v.rend());
		ASSERT(v.rbegin() + 1 == v.rend());

		a = v.rbegin();
		ASSERT(1 + a == v.rend());
		ASSERT(1 + v.rbegin() == v.rend());

		a = v.rend();
		ASSERT(a - 1 == v.rbegin());

		a = v.rend();
		b = v.rbegin();
		ASSERT(a - b == 1);
		ASSERT(v.rend() - v.rbegin() == 1);

		a = v.rend();
		b = v.rbegin();
		ASSERT(a > b);
		ASSERT(v.rend() > v.rbegin());

		a = v.rbegin();
		b = v.rend();
		ASSERT(a < b);
		ASSERT(v.rbegin() < v.rend());

		a = v.rbegin();
		b = v.rbegin();
		ASSERT(a >= b);
		ASSERT(v.rbegin() >= v.rbegin());
		ASSERT(v.rend() >= v.rbegin());
		ASSERT(v.rend() >= v.rend());

		a = v.rbegin();
		b = v.rbegin();
		ASSERT(a <= b);
		ASSERT(v.rbegin() <= v.rbegin());
		ASSERT(v.rbegin() <= v.rend());
		ASSERT(v.rend() <= v.rend());

		a = v.rbegin();
		ASSERT((a += 1) == v.rend());

		a = v.rend();
		ASSERT((a -= 1) == v.rbegin());

		a = v.rbegin();
		ASSERT(a[0] == Aw("42"));

		a = v.rend();
		ASSERT(a[-1] == Aw("42"));
	}

	return (0);
}
