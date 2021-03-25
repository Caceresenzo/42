/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:28:31 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 14:28:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_stack.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		STACK<Aware<int> > q;

		q.push(1);
		ASSERT(q.size() == 1);
		ASSERT(q.top() == 1);

		q.push(2);
		ASSERT(q.size() == 2);
		ASSERT(q.top() == 2);

		q.push(3);
		ASSERT(q.size() == 3);
		ASSERT(q.top() == 3);
	});
}
