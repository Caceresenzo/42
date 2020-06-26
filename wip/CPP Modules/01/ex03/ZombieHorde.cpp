/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstdlib>

#include "ZombieHorde.hpp"
#include "Zombie.hpp"

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(std::string))

std::string
ZombieHorde::NAMES[] = {
	"Adriana", "Alana", "Alissa", "Amalea", "Andra",
	"Annadiane", "Ardath", "Ashlee", "Austin", "Becca", "Berri",
	"Biddy", "Bonnie", "Brittany", "Candi", "Carmelia", "Catarina",
	"Celina", "Cherice", "Chrystal", "Clementina", "Coral", "Courtney",
	"Dalia", "Darla", "Dee Dee", "Devi", "Domeniga", "Dorothy",
	"Eadith", "Eleni", "Else", "Emmye", "Estrella", "Fanchette",
	"Fernande", "Francesca", "Garland", "Germain", "Giuditta", "Gretna",
	"Halli", "Helena", "Horatia", "Inna", "Jacquelyn", "Jannel",
	"Jennette", "Joana", "Jolyn", "Juliann", "Kandace", "Karyn", "Kay",
	"Ki", "Kordula", "Lanae", "Layne", "Leora", "Lillian", "Lizabeth",
	"Lorrin", "Lynda", "Mady", "Marabel", "Marianne", "Marlena",
	"Marysa", "Melamie", "Merla", "Millie", "Mollie", "Nady", "Neille",
	"Nina", "Odella", "Orsa", "Pearline", "Phyllida", "Rakel", "Reina",
	"Roana", "Rosabel", "Roxy", "Sam", "Sena", "Shayna", "Sibbie",
	"Sosanna", "Susannah", "Tammy", "Tersina", "Tine", "Trixy", "Valma",
	"Viola", "Wenonah", "Yettie"
};

std::string
ZombieHorde::TYPES[] = {
	"Walker", "Runner", "Sprinter", "Eater", "Jumper"
};

ZombieHorde::ZombieHorde(int n)
{
	this->_size = n;
	this->_zombies = new Zombie[n];

	for (int index = 0; index < n; ++index)
	{
		this->_zombies[index].setName(NAMES[rand() % ARR_SIZE(NAMES)]);
		this->_zombies[index].setType(TYPES[rand() % ARR_SIZE(TYPES)]);
	}
}

ZombieHorde::~ZombieHorde(void)
{
	delete[] this->_zombies;
}

void
ZombieHorde::announce(void)
{
	for (int index = 0; index < this->_size; ++index)
	{
		Zombie zombie = this->_zombies[index];

		zombie.announce();
	}
}
