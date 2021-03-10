/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.pass.cpp                                       :+:      :+:    :+:   */
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
		STACK<Aware<int> > stack;

		ASSERT(stack.size() == 0);

		stack.push(1);
		stack.push(2);
		stack.push(3);
		ASSERT(stack.size() == 3);
		ASSERT(stack.top() == 3);

		stack.pop();
		ASSERT(stack.size() == 2);
		ASSERT(stack.top() == 2);

		stack.pop();
		ASSERT(stack.size() == 1);
		ASSERT(stack.top() == 1);

		stack.pop();
		ASSERT(stack.size() == 0);
	});
}
