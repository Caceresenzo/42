/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top.pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 14:47:21 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 14:47:21 by ecaceres         ###   ########.fr       */
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
		const STACK<Aware<int> >& cstack = stack;
		const Aware<int> &ctop = cstack.top();
		ASSERT(ctop == 3);
	});
}
