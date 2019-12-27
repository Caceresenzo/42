/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define DEFAULT_MESSAGE "* LOUD AND UNBEARABLE FEEDBACK NOISE *"

int
	main(int argc, char **argv) {
	if (argc <= 1)
		std::cout << DEFAULT_MESSAGE << std::endl;
	else
	{
		for (int index = 1; index < argc; index++) {
			char *str = argv[index];
			char current;

			for (int jndex = 0; (current = str[jndex]); jndex++) {
				if (current >= 'a' && current <= 'z')
				{
					current -= 0x20;
				}

				std::cout << current;
			}
		}

		std::cout << std::endl;
	}
}
