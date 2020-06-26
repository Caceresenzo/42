/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
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
#include "ContactManager.hpp"

int
main(void)
{
	std::string read;
	ContactManager manager;

	while (true)
	{
		std::cout << ASK;
		std::getline(std::cin, read);

		if (std::cin.eof())
		{
			read = CMD_EXIT;
			std::cout << CMD_EXIT << std::endl;
		}

		if (read == CMD_ADD)
		{
			if (manager.canAddMore())
			{
				Contact contact = Contact::creator();

				manager.add(contact);
			}
			else
				std::cout << ERR_PHONEBOOK_FULL << std::endl;
		}
		else if (read == CMD_SEARCH)
		{
			if (!manager.isEmpty())
			{
				manager.listAll();
				manager.interactiveSearch();
			}
		}
		else if (read == CMD_EXIT)
			break;
	}

	return (0);
}
