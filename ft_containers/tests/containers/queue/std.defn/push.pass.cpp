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

#include <unit_queue.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		QUEUE<Aware<int> > queue;

	    queue.push(1);
	    ASSERT(queue.size() == 1);
	    ASSERT(queue.front() == 1);
	    ASSERT(queue.back() == 1);

	    queue.push(2);
	    ASSERT(queue.size() == 2);
	    ASSERT(queue.front() == 1);
	    ASSERT(queue.back() == 2);

	    queue.push(3);
	    ASSERT(queue.size() == 3);
	    ASSERT(queue.front() == 1);
	    ASSERT(queue.back() == 3);
	});
}
