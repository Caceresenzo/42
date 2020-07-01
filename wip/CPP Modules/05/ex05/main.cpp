/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/29 10:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "CentralBureaucracy.hpp"

#define xassert(exp, msg) \
	{ \
		bool ___ok = (exp); \
		if (___ok) \
			std::cout << "\e[92mPASSED\e[39m: " << msg << std::endl; \
		if (!___ok) { \
			std::cout << "\e[91mFAILED\e[39m: " << msg << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

int
main(void)
{
	CentralBureaucracy central;

	for (int index = 0; index < 20; ++index) {
		Bureaucrat bureaucrat("someone powerful", 1);

		central.hire(bureaucrat);
	}

	for (int index = 0; index < 50; ++index) {
		central.queueUp("xxx");
	}

	central.doBureaucracy();
}
