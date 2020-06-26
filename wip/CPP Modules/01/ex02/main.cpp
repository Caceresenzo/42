/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>

#include "Zombie.hpp"
#include "ZombieEvent.hpp"

int
main(void)
{
	srand(time(NULL));

	std::string types[] = { "Walker", "Runner", "Sprinter", "Eater", "Jumper" };
	int count = sizeof(types) / sizeof(std::string);

	ZombieEvent event;

	for(int index = 0; index < count; index++)
	{
		event.setZombieType(types[index]);

		for(int jndex = 0; jndex < 10; jndex++)
		{
			Zombie *zombie = event.randomChump();

			zombie->advert();

			delete zombie;
		}

		std::cout << std::endl;
	}

	event.setZombieType("Royalty");

	Zombie *theKing = event.newZombie("The King");
	theKing->advert();
	delete theKing;

	return (0);
}
