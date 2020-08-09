/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:41:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:41:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "AssaultTerminator.hpp"
#include "Squad.hpp"
#include "TacticalMarine.hpp"

int
main()
{
	ISpaceMarine *bob = new TacticalMarine;
	ISpaceMarine *jim = new AssaultTerminator;

	ISquad *vlc = new Squad;

	vlc->push(bob);
	vlc->push(jim);

	for (int i = 0; i < vlc->getCount(); ++i)
	{
		ISpaceMarine *cur = vlc->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}

	delete vlc;

	std::cout << std::endl << "--- EXTRA ---" << std::endl << std::endl;

	{
		std::cout << std::endl << "==== COPY FROM 3 TO 1" << std::endl << std::endl;

		Squad *squad = new Squad();
		Squad *copy = new Squad();

		std::cout << "->> ADDING TO SRC" << std::endl;
		squad->push(new TacticalMarine());
		squad->push(new TacticalMarine());
		squad->push(new TacticalMarine());

		std::cout << std::endl << "->> ADDING TO DEST" << std::endl;
		copy->push(new AssaultTerminator());

		std::cout << std::endl << "->> COPY START" << std::endl;
		*copy = *squad;
		std::cout << "->> COPY END" << std::endl << std::endl;

		std::cout << "original: " << squad->getCount() << std::endl;
		std::cout << "copy: " << copy->getCount() << std::endl;

		std::cout << std::endl << "->> DELETE" << std::endl << std::endl;
		delete squad;
		delete copy;
	}

	{
		std::cout << std::endl << "==== COPY FROM 1 TO 3" << std::endl << std::endl;

		Squad *squad = new Squad();
		Squad *copy = new Squad();

		std::cout << "->> ADDING TO SRC" << std::endl;
		squad->push(new AssaultTerminator());

		std::cout << std::endl << "->> ADDING TO DEST" << std::endl;
		copy->push(new TacticalMarine());
		copy->push(new TacticalMarine());
		copy->push(new TacticalMarine());

		std::cout << std::endl << "->> COPY START" << std::endl;
		*copy = *squad;
		std::cout << "->> COPY END" << std::endl << std::endl;

		std::cout << "original: " << squad->getCount() << std::endl;
		std::cout << "copy: " << copy->getCount() << std::endl;

		std::cout << std::endl << "->> DELETE" << std::endl << std::endl;
		delete squad;
		delete copy;
	}

	{
		std::cout << std::endl << "==== COPY FROM 3 TO 3" << std::endl << std::endl;

		Squad *squad = new Squad();
		Squad *copy = new Squad();

		std::cout << "->> ADDING TO SRC" << std::endl;
		squad->push(new AssaultTerminator());
		squad->push(new AssaultTerminator());
		squad->push(new AssaultTerminator());

		std::cout << std::endl << "->> ADDING TO DEST" << std::endl;
		copy->push(new TacticalMarine());
		copy->push(new TacticalMarine());
		copy->push(new TacticalMarine());

		std::cout << std::endl << "->> COPY START" << std::endl;
		*copy = *squad;
		std::cout << "->> COPY END" << std::endl << std::endl;

		std::cout << "original: " << squad->getCount() << std::endl;
		std::cout << "copy: " << copy->getCount() << std::endl;

		std::cout << std::endl << "->> DELETE" << std::endl << std::endl;
		delete squad;
		delete copy;
	}

	{
		std::cout << std::endl << "==== DELETE A LOT AT SQUAD FREE" << std::endl << std::endl;

		Squad *squad = new Squad();

		std::cout << "->> ADDING" << std::endl;
		for (int index = 0; index < 20; ++index)
		{
			if (index % 2)
				squad->push(new AssaultTerminator());
			else
				squad->push(new TacticalMarine());
		}

		std::cout << std::endl << "->> DELETING" << std::endl;
		delete squad;
	}

	{
		std::cout << std::endl << "==== GET AT" << std::endl << std::endl;

		Squad *squad = new Squad();

		std::cout << "->> ADDING" << std::endl;
		for (int index = 0; index < 20; ++index)
		{
			if (index % 2)
				squad->push(new AssaultTerminator());
			else
				squad->push(new TacticalMarine());
		}

		std::cout << std::endl << "->> USING ATTACK" << std::endl;
		for (int index = -2; index < 23; ++index)
		{
			ISpaceMarine *marine = squad->getUnit(index);

			std::cout << '[' << index << "] = " << marine << std::endl;

			if (marine)
				marine->meleeAttack();

			std::cout << std::endl;
		}

		std::cout << std::endl << "->> DELETING" << std::endl;
		delete squad;
	}

	return (EXIT_SUCCESS);
}
