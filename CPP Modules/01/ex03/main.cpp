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

#include <string>
#include <ctime>
#include <stdlib.h>

#include "Zombie.hpp"
#include "ZombieHorde.hpp"

int
main(void)
{
	srand(time(NULL));

	ZombieHorde horde = ZombieHorde(10);

	horde.announce();

	return (0);
}
