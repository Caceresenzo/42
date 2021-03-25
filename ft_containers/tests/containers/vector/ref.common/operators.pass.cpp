/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.pass.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:35:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:35:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unit_vector.hpp>

int
main(void)
{
	{
		VECTOR<int> foo(3, 100);
		VECTOR<int> bar(2, 200);

		ASSERT((foo == bar) == false);
		ASSERT((foo != bar) == true);
		ASSERT((foo < bar) == true);
		ASSERT((foo > bar) == false);
		ASSERT((foo <= bar) == true);
		ASSERT((foo >= bar) == false);
	};

	return (0);
}
