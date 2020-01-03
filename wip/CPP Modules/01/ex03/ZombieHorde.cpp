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

#include "ZombieHorde.hpp"
#include "Zombie.hpp"

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
	this->_zombies = (Zombie *)malloc(n * sizeof(Zombie));

	if (this->_zombies != NULL)
	{
		for (int index = 0; index < n; ++index)
		{
			Zombie *zombie = (Zombie *)(this->_zombies + index);

			std::string name = NAMES[rand() % (sizeof(NAMES) / sizeof(std::string))];
			std::string type = TYPES[rand() % (sizeof(TYPES) / sizeof(std::string))];

			zombie->_name = name;
			zombie->_type = type;
		}
	}
}

ZombieHorde::~ZombieHorde(void)
{
	delete this->_zombies;
}

void
ZombieHorde::advert(void)
{
	for (int index = 0; index < this->_size; ++index)
	{
		Zombie *zombie = (Zombie *)(this->_zombies + index);

		zombie->advert();
	}
}
