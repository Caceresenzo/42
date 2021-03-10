/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.pass.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 15:24:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/10 15:24:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_queue.hpp>

int
main(void)
{
	TEST_AWARE_BLOCK({
		QUEUE<Aware<int> > queue;

		ASSERT(queue.size() == 0);

		queue.push(1);
		queue.push(2);
		queue.push(3);
		const QUEUE<Aware<int> >& cqueue = queue;
		const Aware<int> &cback = cqueue.back();
		ASSERT(cback == 3);
	});
}
