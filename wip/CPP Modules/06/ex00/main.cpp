/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:54:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/01 11:54:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "Number.hpp"

#ifndef MULTI
# define MULTI false
#endif

int
main(int argc, char **argv)
{
	if (argc == 1 || (!MULTI && argc > 2))
	{
		std::cout << "usage: " << argv[0];

		if (MULTI)
			std::cout << " <scalar ...>";
		else
			std::cout << " <scalar>";

		std::cout << std::endl;

		return (EXIT_FAILURE);
	}

	bool success = true;

	if (MULTI)
	{
		for (int index = 1; index < argc; ++index)
		{
			std::cout << argv[index] << std::endl;
			success &= Number::dump(std::string(argv[index]));
			std::cout << std::endl;
		}
	}
	else
		success = Number::dump(std::string(argv[1]));

	return (success ? EXIT_SUCCESS : EXIT_FAILURE);
}
