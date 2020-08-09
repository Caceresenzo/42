/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CentralBureaucracy.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:55:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 18:55:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>

#include "CentralBureaucracy.hpp"

CentralBureaucracy::CentralBureaucracy()
{
}

CentralBureaucracy::~CentralBureaucracy()
{
	for (int index = 0; index < OFFICE_BLOCK_TOTAL; ++index)
	{
		OfficeBlock &block = this->_officeBlocks[index];

		if (block.getIntern())
			delete block.removeIntern();

		if (block.getSigner() && block.getSigner() != block.getExecutor())
			delete block.removeSigner();

		if (block.getExecutor())
			delete block.removeExecutor();
	}
}

CentralBureaucracy::CentralBureaucracy(const CentralBureaucracy &other)
{
	this->operator =(other);
}

CentralBureaucracy&
CentralBureaucracy::operator=(const CentralBureaucracy &other)
{
	(void)other;

	return (*this);
}

bool
CentralBureaucracy::hire(Bureaucrat &bureaucrat)
{
	for (int index = 0; index < OFFICE_BLOCK_TOTAL; ++index)
	{
		OfficeBlock &block = this->_officeBlocks[index];

		if (!block.getIntern())
			block.setIntern(*(new Intern()));

		if (!block.getSigner())
		{
			block.setSigner(*(new Bureaucrat(bureaucrat)));
			return (true);
		}

		if (!block.getExecutor())
		{
			block.setExecutor(*(new Bureaucrat(bureaucrat)));
			return (true);
		}
	}

	return (false);
}

bool
CentralBureaucracy::queueUp(std::string targetToQueue)
{
	if (!targetToQueue.empty())
	{
		for (int index = 0; index < TARGET_QUEUE_SIZE; ++index)
		{
			std::string &at = this->_targets[index];

			if (at.empty())
			{
				at = targetToQueue;

				return (true);
			}
		}
	}

	return (false);
}
void
CentralBureaucracy::doBureaucracy()
{
	int workable = this->workableOffice();

	int targetIndex = 0;
	std::string currentTarget;

	int officeIndex = 0;

	try
	{
		while (targetIndex < TARGET_QUEUE_SIZE
		        && !(currentTarget = this->_targets[targetIndex++]).empty())
		{
			std::cout << std::endl << "Central: processing target #"
			        << (targetIndex - 1) << std::endl;

			if (officeIndex >= workable || officeIndex >= OFFICE_BLOCK_TOTAL)
				officeIndex = 0;

			OfficeBlock &block = this->_officeBlocks[officeIndex++];

			block.doBureaucracy(Intern::FORM_NAMES[rand() % FORM_IMPL_COUNT], currentTarget);
		}
	}
	catch (std::exception &e)
	{
		for (int index = 0; index < TARGET_QUEUE_SIZE; ++index)
			this->_targets[index] = "";

		std::cout << "Failed to do bureaucracy: " << e.what() << std::endl;
	}
}

int
CentralBureaucracy::workableOffice()
{
	int count = 0;

	for (int index = 0; index < OFFICE_BLOCK_TOTAL; ++index)
	{
		count += this->_officeBlocks[index].canWork();
	}

	return (count);
}

void
CentralBureaucracy::ensureNotLocked()
{
}
