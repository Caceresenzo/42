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

int
main(void)
{
	srand(time(0));

	FragTrap fragTrap("Unit 1");

	fragTrap.rangedAttack("The Kind");
	fragTrap.meleeAttack("The Queen");

	fragTrap.takeDamage(10);
	fragTrap.beRepaired(10);
	// Energy = 95

	fragTrap.takeDamage(50);
	fragTrap.beRepaired(100);
	// Energy = 50

	fragTrap.takeDamage(50);
	fragTrap.beRepaired(100);
	// Energy = 5

	fragTrap.takeDamage(15);
	fragTrap.beRepaired(15); // Needed 10
	// Energy = -5 --> not enought

	fragTrap.takeDamage(1000);

	FragTrap fragTrap2("Unit 2");

	fragTrap2.vaulthunter_dot_exe("Human");
	fragTrap2.vaulthunter_dot_exe("Sorcerer");
	fragTrap2.vaulthunter_dot_exe("Knight");
	fragTrap2.vaulthunter_dot_exe("Giant");
	fragTrap2.vaulthunter_dot_exe("Ant");
}
