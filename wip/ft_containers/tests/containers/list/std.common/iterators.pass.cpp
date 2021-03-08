/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.pass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:02:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 14:02:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

struct A
{
    Aware<int> first;
    Aware<int> second;
};

int
main(void)
{
    {
        typedef Aware<int> T;
        typedef LIST<T> C;

        C c;
        C::iterator i = c.begin();
        C::iterator j = c.end();

        ASSERT(DISTANCE(i, j) == 0);
        ASSERT(i == j);
    }

    ASSERT_AWARE_ZERO();

    {
        typedef Aware<int> T;
        typedef LIST<T> C;

        const C c;
        C::const_iterator i = c.begin();
        C::const_iterator j = c.end();

        ASSERT(DISTANCE(i, j) == 0);
        ASSERT(i == j);
    }

    ASSERT_AWARE_ZERO();

    {
        typedef Aware<int> T;
        typedef LIST<T> C;

        const T t[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        C c(t, t + sizeof(t) / sizeof(t[0]));
        C::iterator i = c.begin();

        ASSERT(*i == 0);

        ++i;
        ASSERT(*i == 1);

        *i = 10;
        ASSERT(*i == 10);
        ASSERT(DISTANCE(c.begin(), c.end()) == 10);
    }

    ASSERT_AWARE_ZERO();

    {
        typedef Aware<int> T;
        typedef LIST<T> C;

        C::iterator i;
        C::const_iterator j;
    }

    ASSERT_AWARE_ZERO();
}
