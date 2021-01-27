/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:06:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 16:06:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <log/LoggerFactory.hpp>
#include <log/LoggerImpl.hpp>
#include <utility>

Logger&
LoggerFactory::get(const std::string &tag)
{
	logger_map &storage = getStorage();

	iterator it = storage.find(tag);
	if (it == storage.end())
		it = storage.insert(storage.end(), std::pair<std::string, Logger*>(tag, new LoggerImpl(tag)));

	return (*it->second);
}

void
LoggerFactory::destroy(void)
{
	logger_map &storage = getStorage();

	for (iterator it = storage.begin(); it != storage.end(); it++)
		delete it->second;

	storage.clear();
}

LoggerFactory::logger_map&
LoggerFactory::getStorage()
{
	static logger_map storage;

	return (storage);
}
