/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPFindLocation.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:24:50 by alicetetu         #+#    #+#             */
/*   Updated: 2021/01/26 12:06:48 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/LocationBlock.hpp>
#include <http/route/HTTPFindLocation.hpp>
#include <http/route/HTTPLocationInterpretor.hpp>
#include <cstddef>
#include <iostream>
#include <list>
#include <string>

HTTPFindLocation::HTTPFindLocation() :
		m_clientPath(""),
		m_serverLocations(),
		m_locationBlock()
{
}

HTTPFindLocation::HTTPFindLocation(std::string clientPath, std::list<const LocationBlock*> serverLocations) :
		m_clientPath(clientPath),
		m_serverLocations(serverLocations),
		m_locationBlock()
{
}

HTTPFindLocation::HTTPFindLocation(const HTTPFindLocation &other) :
		m_clientPath(other.m_clientPath),
		m_serverLocations(other.m_serverLocations),
		m_locationBlock(other.m_locationBlock)
{
}

HTTPFindLocation::~HTTPFindLocation()
{
}

HTTPFindLocation&
HTTPFindLocation::operator =(const HTTPFindLocation &other)
{
	if (this != &other)
	{
		m_clientPath = other.m_clientPath;
		m_serverLocations = other.m_serverLocations;
		m_locationBlock = other.m_locationBlock;
	}
	return (*this);
}

HTTPFindLocation&
HTTPFindLocation::location(const LocationBlock *locationBlock)
{
	m_locationBlock.set(locationBlock);

	return (*this);
}

const Optional<const LocationBlock*>
HTTPFindLocation::location(void) const
{
	return (m_locationBlock);
}

#define NEXT_LOOP(it)		\
	{						\
		it++;				\
		continue;			\
	}

#define FIND_BEST(possibleLocationList, it_PossibleLoc, ite_PossibleLoc,loc, apply)					\
	while (it_PossibleLoc != ite_PossibleLoc)														\
	{																								\
		if (it_PossibleLoc->apply().size() > loc.begin()->start().size())							\
		{																							\
			loc.pop_back();																			\
			loc.push_back(*it_PossibleLoc);															\
		}																							\
		it_PossibleLoc++;																			\
	}																								\
	it_PossibleLoc = possibleLocationList.begin();

#define FIND_BEST_MIDDLE(possibleLocationList, it_PossibleLoc, ite_PossibleLoc,loc, apply)			\
	while (it_PossibleLoc != ite_PossibleLoc)														\
	{																								\
		std::list<std::string> &middleList = it_PossibleLoc->apply();								\
		std::list<std::string>::iterator it_MiddleList = middleList.begin();						\
		std::list<std::string>::iterator ite_MiddleList = middleList.end();							\
		while (it_MiddleList != ite_MiddleList)														\
		{																							\
			if (it_MiddleList->size() > loc.begin()->start().size())								\
			{																						\
				loc.pop_back();																		\
				loc.push_back(*it_PossibleLoc);														\
			}																						\
			else																					\
				break;																				\
			it_MiddleList++;																		\
		}																							\
																									\
		it_PossibleLoc++;																			\
	}																								\
	it_PossibleLoc = possibleLocationList.begin();

HTTPFindLocation&
HTTPFindLocation::parse(void)
{
	std::list<const LocationBlock*>::iterator it = m_serverLocations.begin();
	std::list<const LocationBlock*>::iterator ite = m_serverLocations.end();

	int start;
	int endIndicator;
	int middle;
	std::size_t pos;
	std::size_t new_pos;
	int not_found_middle;
	bool exactEnd = false;

	std::list<HTTPLocationInterpretor> possibleLocationList;
	std::list<HTTPLocationInterpretor> exactEndList;
	
	while (it != ite)
	{
		HTTPLocationInterpretor interpretor((*it)->path(), *it);

		char c;
		start = 0;
		endIndicator = 0;
		middle = 0;
		pos = 0;
		new_pos = 0;
		not_found_middle = 0;

		while (interpretor.next(c))
			interpretor.consume(c);

		if (!(interpretor.middleElement().empty()))
		{
			interpretor.middleList(interpretor.middleElement());
		}
		
		if (interpretor.lastChar() != '*' && !interpretor.middleList().empty())
		{
			std::string it_middleListEnd = interpretor.middleList().back();
			interpretor.setEnd(it_middleListEnd);
			interpretor.erase();
		}

		if (!(interpretor.exact().empty()))
		{
			if (interpretor.exact().compare(m_clientPath) == 0 || interpretor.exact().compare(m_clientPath + "/") == 0)
				possibleLocationList.push_back(interpretor);

			NEXT_LOOP(it);
		}
	
		if (interpretor.firstChar() != '*')
		{
	
			if (!(interpretor.start().empty()))
		{
			if (m_clientPath.compare(0, interpretor.start().size(), interpretor.start()) == 0 || (m_clientPath + "/").compare(0, interpretor.start().size(), interpretor.start()) == 0)
			{
				start = 1;
				pos = interpretor.start().size();
			}
			else
				NEXT_LOOP(it);
		}

			
		}
		else
		{
			exactEnd = true;
		}
				
		if (!(interpretor.middleList().empty()))
		{
			std::list<std::string>::iterator it_list = interpretor.middleList().begin();
			std::list<std::string>::iterator ite_list = interpretor.middleList().end();
			while (it_list != ite_list)
			{
				if ((new_pos = m_clientPath.find(*it_list)))
				{
					if (new_pos >= pos)
						pos = new_pos + (*it_list).size() + 1;
					else
					{
						not_found_middle = 1;
						break;;
					}
				}
				else
				{
					not_found_middle = 1;
					break;;
				}
				it_list++;
			}
			if (not_found_middle)
			{
				NEXT_LOOP(it);
			}

			middle = 1;
		}
		if (!(interpretor.end().empty()))
		{
			std::string end = interpretor.end();

			int size = end.size();
			int index = m_clientPath.size() - size;
		
			if (index >= 0 && (m_clientPath.compare(index, size, end) == 0 || (m_clientPath + "/").compare(index, size, end) == 0))
			{
				endIndicator = 1;
			}
			else
				NEXT_LOOP(it);
		}

		if (start || middle || endIndicator)
		{
			if (exactEnd)
			{
				exactEndList.push_back(interpretor);
			}
			else
				possibleLocationList.push_back(interpretor);
		}
		it++;
	}

	std::list<HTTPLocationInterpretor> &listToCheck = possibleLocationList;
	if (!exactEndList.empty())
	{
		listToCheck.clear();
		listToCheck = exactEndList;
	}
	std::list<HTTPLocationInterpretor>::iterator it_listToCheck = listToCheck.begin();
	std::list<HTTPLocationInterpretor>::iterator ite_listToCheck = listToCheck.end();

	std::list<HTTPLocationInterpretor> loc;
	loc.push_back(*it_listToCheck);
	
	FIND_BEST(listToCheck, it_listToCheck, ite_listToCheck, loc, start);
	FIND_BEST_MIDDLE(listToCheck, it_listToCheck, ite_listToCheck, loc, middleList);
	FIND_BEST(listToCheck, it_listToCheck, ite_listToCheck, loc, end);

	HTTPLocationInterpretor &bestLocation = *(loc.begin());

	location(bestLocation.locationBlock());
	
	return (*this);
}
