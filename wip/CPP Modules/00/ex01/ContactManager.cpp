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
	std::memset(this->contacts, 0, sizeof(this->contacts));
}

ContactManager::~ContactManager(void)
{
	for (int index = 0; index < MAX_CONTACT; index++)
	{
		Contact *current = this->contacts[index];

		if (current == NULL)
		{
			break ;
		}

		delete current;
	}
}

int
	ContactManager::getNextAvailableSlot(void)
{
	for (int index = 0; index < MAX_CONTACT; index++)
	{
		Contact *current = this->contacts[index];

		if (current == NULL)
		{
			return (index);
		}
	}
	return (-1);
}

bool
	ContactManager::canAddMore(void)
{
	return (this->getNextAvailableSlot() != -1);
}

int
	ContactManager::size(void)
{
	int index = 0;

	for (; index < MAX_CONTACT; index++)
	{
		Contact *current = this->contacts[index];

		if (current == NULL)
		{
			break ;
		}
	}
	return (index);
}

bool
	ContactManager::isEmpty(void)
{
	return (this->size() == 0);
}

bool
	ContactManager::add(Contact *contact)
{
	int nextSlot = this->getNextAvailableSlot();

	if (nextSlot == -1)
	{
		return (false);
	}

	this->contacts[nextSlot] = contact;

	return (true);
}

void
	ContactManager::display(Contact *contact)
{
	std::string *fields[Contact::INPUT_COUNT];
	contact->getFields(fields);

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
		Contact *current = this->contacts[index];

		std::stringstream indexStream;
		indexStream << index;

		TableRenderer::renderColumnEntry(indexStream.str());
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current->first_name);
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current->last_name);
		TableRenderer::renderBorder(false);

		TableRenderer::renderColumnEntry(current->nickname);
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
		{
			std::cout << std::endl;
		}
		else
		{
			if (out_of_bound)
			{
				std::cout << ERR_SEARCH_OUT_OF_BOUNDS << std::endl;
			}
			else
			{
				std::cout << ERR_SEARCH_INVALID_INDEX_INPUT << std::endl;
			}
		}
		return ;
	}

	Contact *selected = this->contacts[index];

	this->display(selected);
}
