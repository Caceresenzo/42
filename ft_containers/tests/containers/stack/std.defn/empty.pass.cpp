/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.pass.cpp                                     :+:      :+:    :+:   */
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
	    ASSERT(stack.empty());

	    stack.push(1);
	    ASSERT(!stack.empty());

	    stack.pop();
	    ASSERT(stack.empty());
	});
}
