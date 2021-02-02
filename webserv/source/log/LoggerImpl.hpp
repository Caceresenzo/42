/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerImpl.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:54:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 10:54:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGERIMPL_HPP_
# define LOGGERIMPL_HPP_

#include <log/Logger.hpp>
#include <iostream>
#include <string>
#include <sstream>

class NullStream :
		public std::stringstream
{
	public:
		NullStream() :
				std::stringstream()
		{
		}
};

template<typename T>
	void
	operator<<(const NullStream&, const T&)
	{
	}

class LoggerImpl :
		public Logger
{
	private:
		static size_t LONGEST_NAME;
		static const std::string DEFAULT_TAG;
		static NullStream VOID;

	private:
		std::string m_tag;

	public:
		LoggerImpl(void);
		LoggerImpl(const std::string &tag);
		LoggerImpl(const LoggerImpl &other);

		virtual
		~LoggerImpl();

		std::ostream&
		trace() const;

		std::ostream&
		debug() const;

		std::ostream&
		info() const;

		std::ostream&
		warn() const;

		std::ostream&
		error() const;

		std::ostream&
		fatal() const;

		std::ostream&
		log(const LogLevel &level) const;

		const std::string&
		tag() const;

		bool
		isEnabled(const LogLevel &logLevel) const;
};

#endif /* LOGGERIMPL_HPP_ */
