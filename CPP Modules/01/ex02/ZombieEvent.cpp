/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <stdlib.h>

#include "ZombieEvent.hpp"
#include "Zombie.hpp"

/*
** https://github.com/dominictarr/random-name/blob/master/first-names.json
** Filtered to: (index + 1) % 50 == 0
*/

std::string
ZombieEvent::NAMES[] = {
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

ZombieEvent::ZombieEvent(void)
{
	;
}

void
ZombieEvent::setZombieType(std::string type)
{
	this->_type = type;
}

Zombie
*ZombieEvent::newZombie(std::string name)
{
	return (new Zombie(name, this->_type));
}

Zombie
*ZombieEvent::randomChump(void)
{
	int random = rand() % (sizeof(NAMES) / sizeof(std::string));
	std::string name = NAMES[random];

	return (newZombie(name));
}
