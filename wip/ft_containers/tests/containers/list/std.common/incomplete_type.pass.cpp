/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_type.pass.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 14:03:25 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 14:03:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_list.hpp>

struct A {
    LIST<A> l;
    LIST<A>::iterator it;
    LIST<A>::const_iterator cit;
    LIST<A>::reverse_iterator rit;
    LIST<A>::const_reverse_iterator crit;
};

struct B {
    LIST<Aware<B> > l;
    LIST<Aware<B> >::iterator it;
    LIST<Aware<B> >::const_iterator cit;
    LIST<Aware<B> >::reverse_iterator rit;
    LIST<Aware<B> >::const_reverse_iterator crit;
};

int
main(void)
{
    {
        A a;
    }

    {
        B b;
    }

    ASSERT_AWARE_ZERO();
}
