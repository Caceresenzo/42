/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:21:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 18:21:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "Character.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "RadScorpion.hpp"
#include "SuperMutant.hpp"

int
main()
{
	Character *moi = new Character("moi");

	std::cout << *moi;

	Enemy *b = new RadScorpion();
	AWeapon *pr = new PlasmaRifle();
	AWeapon *pf = new PowerFist();

	moi->equip(pr);
	std::cout << *moi;
	moi->equip(pf);

	moi->attack(b);
	std::cout << *moi;
	moi->equip(pr);
	std::cout << *moi;
	moi->attack(b);
	std::cout << *moi;
	moi->attack(b);
	std::cout << *moi;


	std::cout << std::endl << "--- EXTRA ---" << std::endl << std::endl;

	Character him("him");
	PlasmaRifle rifle = PlasmaRifle();
	Enemy *enemy = new SuperMutant();

	std::cout << std::endl << "==== HEAP TEST" << std::endl << std::endl;
	him.equip(&rifle);
	std::cout << him;
	him.equip(&rifle);
	std::cout << him;

	std::cout << std::endl << "==== DAMAGE TEST" << std::endl << std::endl;
	std::cout << "weapon attack: " << rifle.getDamage() << std::endl;
	std::cout << "enemy health before: " << enemy->getHp() << std::endl;
	him.attack(enemy);
	std::cout << "enemy health after: " << enemy->getHp() << std::endl;
	std::cout << him;

	std::cout << std::endl << "==== OUT OF AP TEST" << std::endl << std::endl;
	for (int index = 0; index < 10; ++index) {
		him.attack(enemy);
		std::cout << him;
	}

	std::cout << std::endl << "==== RECOVER AP TEST" << std::endl << std::endl;

	for (int index = 0; index < 6; ++index) {
		him.recoverAP();
		std::cout << him;
	}

	std::cout << std::endl << "==== KILL TEST" << std::endl << std::endl;
	him.attack(enemy);
	him.attack(enemy);

	delete moi;
	delete pr;
	delete pf;

	std::cout << std::endl << "--- EXTRA END ---" << std::endl;

	return (EXIT_SUCCESS);
}
