/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:18:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 10:18:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"

int
main(void)
{
	srand(time(0));

	FragTrap fragTrap("The Fragger");
	ScavTrap scavTrap("The Scaver");
	NinjaTrap ninjaTrap("The Ninja");

	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);

	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);

	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);
}
