/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContactManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>

#include "Phonebook.hpp"
#include "ContactManager.hpp"
#include "Common.hpp"
#include "TableRenderer.hpp"

ContactManager::ContactManager(void)
{
	this->added = 0;
}

bool
ContactManager::canAddMore(void)
{
	return (this->size() < MAX_CONTACT);
}

int
ContactManager::size(void)
{
	return (this->added);
}

bool
ContactManager::isEmpty(void)
{
	return (this->size() == 0);
}

bool
ContactManager::add(Contact contact)
{
	if (!this->canAddMore())
		return (false);

	this->contacts[this->added++] = contact;

	return (true);
}

void
ContactManager::display(Contact contact)
{
	std::string *fields[Contact::INPUT_COUNT];
	contact.fields(fields);

	for (int index = 0; index < Contact::INPUT_COUNT; index++)
	{
		std::string input = Contact::INPUTS[index];
		std::string *field = fields[index];

		std::cout << input << DISPLAY_CONTACT_INFO << *field << std::endl;
	}
}

void
ContactManager::listAll(void)
{
	const int size = this->size();

	for (int index = 0; index < size; index++)
	{
		Contact current = this->contacts[index];

		std::stringstream indexStream;
		indexStream << index;

		TableRenderer::renderColumnEntry(indexStream.str());
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current.getFirstName());
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current.getLastName());
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current.getNickname());
		TableRenderer::renderBorder(true);
	}
}

void
ContactManager::interactiveSearch(void)
{
	std::cout << ASK_INDEX;

	std::string read;
	int index = -1;

	bool invalid_input = !std::getline(std::cin, read) || !Common::strict_positive_atoi(read.c_str(), &index, '\n');
	bool out_of_bound = index < 0 || index >= MAX_CONTACT || index >= this->size();

	if (invalid_input || out_of_bound)
	{
		if (std::cin.eof())
			std::cout << std::endl;
		else
		{
			if (!invalid_input && out_of_bound && !read.empty())
				std::cout << ERR_SEARCH_OUT_OF_BOUNDS << std::endl;
			else
				std::cout << ERR_SEARCH_INVALID_INDEX_INPUT << std::endl;
		}

		return;
	}

	this->display(this->contacts[index]);
}
