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

#include <unit_queue.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
	    QUEUE<Aware<int> > queue;
	    ASSERT(queue.empty());

	    queue.push(1);
	    ASSERT(!queue.empty());

	    queue.pop();
	    ASSERT(queue.empty());
	});
}
