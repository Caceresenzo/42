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
#include "Common.hpp"

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
	;
}

void
Contact::fields(std::string *fields[])
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

	for (int index = 0; index < Contact::INPUT_COUNT; ++index)
		fields[index] = local[index];
}

Contact
Contact::creator(void)
{
	Contact contact;

	std::string *fields[Contact::INPUT_COUNT];
	contact.fields(fields);

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
			break;
		}

		*field = read;
	}

	return (contact);
}

std::string
Contact::getFirstName()
{
	return this->first_name;
}

std::string
Contact::getLastName()
{
	return this->last_name;
}

std::string
Contact::getNickname()
{
	return this->nickname;
}
