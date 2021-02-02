/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:10:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 16:10:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libs/ft.hpp>
#include <util/Environment.hpp>
#include <iostream>
#include <utility>

Environment Environment::PROGRAM;

Environment::Environment() :
		m_storage()
{
}

Environment::Environment(map storage) :
		m_storage(storage)
{
}

Environment::Environment(const Environment &other) :
		m_storage(other.m_storage)
{
}

Environment::~Environment()
{
}

Environment&
Environment::operator =(const Environment &other)
{
	if (this != &other)
		m_storage = other.m_storage;

	return (*this);
}

bool
Environment::hasProperty(const std::string &key)
{
	return (m_storage.find(key) != m_storage.end());
}

bool
Environment::setProperty(const std::string &key, const std::string &value, bool onlyIfMissing)
{
	iterator it = m_storage.find(key);

	if (it == m_storage.end())
	{
		m_storage.insert(it, std::make_pair(key, value));
		return (true);
	}

	if (onlyIfMissing)
		return (false);

	it->second = value;

	return (true);
}

char**
Environment::allocate() const
{
	char **envp = new char*[m_storage.size() + 1];

	map::size_type index = 0;
	for (const_iterator it = m_storage.begin(); it != m_storage.end(); it++)
	{
		std::string line = it->first + '=' + it->second;
		envp[index++] = ft::strdup(line.c_str());
	}

	envp[index] = NULL;

	return (envp);
}

Environment
Environment::fromEnvp(char **envp)
{
	Environment environment;

	char *str;
	while ((str = *envp))
	{
		char *equal = ft::strchr(str, '=');
		const char *value = "";

		if (equal)
		{
			equal[0] = '\0';
			value = equal + 1;
		}

		environment.setProperty(str, value);

		if (equal)
			equal[0] = '=';

		envp++;
	}

	return (environment);
}

void
Environment::set(char **envp)
{
	PROGRAM = fromEnvp(envp);
}

Environment&
Environment::get()
{
	return (PROGRAM);
}

std::string
Environment::join(const std::string &separator) const
{
	std::string out;
	for (const_iterator it = m_storage.begin(); it != m_storage.end();)
	{
		out += it->first + '=' + it->second;

		if (++it != m_storage.end())
			out += separator;
	}

	return (out);
}
