/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Environment.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:10:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 16:10:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_HPP_
# define ENVIRONMENT_HPP_

#include <exception/Exception.hpp>
#include <map>
#include <string>

class Environment
{
	public:
		typedef std::map<std::string, std::string> map;
		typedef map::iterator iterator;
		typedef map::const_iterator const_iterator;

	private:
		static Environment PROGRAM;

	private:
		map m_storage;

	public:
		Environment(void);
		Environment(map storage);
		Environment(const Environment &other);

		virtual
		~Environment(void);

		Environment&
		operator=(const Environment &other);

		bool
		hasProperty(const std::string &key);

		template<typename T>
			T
			getProperty(const std::string &key, const T &defaultValue = T());

		bool
		setProperty(const std::string &key, const std::string &value, bool onlyIfMissing = false);

		char**
		allocate() const;

		std::string
		join(const std::string &separator = " ") const;

	public:
		static Environment
		fromEnvp(char **envp);

		static void
		set(char **envp);

		static Environment&
		get();
};

template<>
	inline std::string
	Environment::getProperty(const std::string &key, const std::string &defaultValue)
	{
		iterator it = m_storage.find(key);

		if (it == m_storage.end())
			return (defaultValue);

		return (it->second);
	}

template<typename T>
	inline T
	Environment::getProperty(const std::string &key, const T &defaultValue)
	{
		(void)key;
		(void)defaultValue;

		throw Exception("Unsupported type");
	}

#endif /* ENVIRONMENT_HPP_ */
