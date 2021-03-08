/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:18:00 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 23:18:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

struct Payload
{
		int val;
		int side;

		Payload(int v) :
				val(v),
				side(0)
		{
		}

		Payload(int v, int s) :
				val(v),
				side(s)
		{
		}

		bool
		operator<(const Payload &rhs) const
		{
			return val < rhs.val;
		}
};
//
//void test_stable(int N)
//{
//    typedef Payload T;
//    typedef LIST<T> C;
//    typedef std::vector<T> V;
//    V v;
//    for (int i = 0; i < N; ++i)
//        v.push_back(Payload(i/2));
//    std::shuffle(v.begin(), v.end(), randomness);
//    for (int i = 0; i < N; ++i)
//        v[i].side = i;
//
//    C c(v.begin(), v.end());
//    c.sort();
//    assert(distance(c.begin(), c.end()) == N);
//
////  Are we sorted?
//    typename C::const_iterator j = c.begin();
//    for (int i = 0; i < N; ++i, ++j)
//        assert(j->val == i/2);
//
////  Are we stable?
//    for (C::const_iterator it = c.begin(); it != c.end(); ++it)
//    {
//        C::const_iterator next = std::next(it);
//        if (next != c.end() && it->val == next->val)
//            assert(it->side < next->side);
//    }
//}

int
main(void)
{
	{
		int a1[] = { 4, 8, 1, 0, 5, 7, 2, 3, 6, 11, 10, 9 };
		int a2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		LIST<Aware<int> > c1(a1, a1 + sizeof(a1) / sizeof(a1[0]));

		c1.sort();
		ASSERT(c1 == LIST<Aware<int> >(a2, a2 + sizeof(a2) / sizeof(a2[0])));
	}

	ASSERT_AWARE_ZERO();

//    for (int i = 0; i < 40; ++i)
//        test_stable(i);

  return 0;
}
