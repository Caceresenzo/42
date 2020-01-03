/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Phonebook.hpp"
#include "Contact.hpp"

const std::string Contact::INPUTS[] = {
	"First Name",
	"Last Name",
	"Nickname",
	"Login",
	"Postal Address",
	"Email Address",
	"Phone Number",
	"Birthday Date",
	"Favorite Meal",
	"Underwear Color",
	"Darkest Secret",
};

const int Contact::INPUT_COUNT = sizeof(Contact::INPUTS) / sizeof(std::string);

Contact::Contact(void)
{
	return ;
}

void
	Contact::getFields(std::string *fields[])
{
	std::string *local[] = {
		&(this->first_name),
		&(this->last_name),
		&(this->nickname),
		&(this->login),
		&(this->postal_address),
		&(this->email_address),
		&(this->phone_number),
		&(this->birthday_date),
		&(this->favorite_meal),
		&(this->underwear_color),
		&(this->darkest_secret),
	};
	std::memcpy(fields, local, sizeof(local));
}

Contact
	*Contact::creator(void)
{
	Contact* contact = new Contact();

	std::string *fields[Contact::INPUT_COUNT];
	contact->getFields(fields);

	for (int index = 0; index < Contact::INPUT_COUNT; index++)
	{
		std::string input = Contact::INPUTS[index];
		std::string *field = fields[index];

		std::cout << input << ASK_CONTACT_INFO;

		std::string read;
		std::getline(std::cin, read);

		if (std::cin.eof())
		{
			std::cout << std::endl;
			break ;
		}

		*field = read;
	}

	return (contact);
}
