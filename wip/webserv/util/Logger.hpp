/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 10:54:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/20 10:54:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_UTIL_LOGGER_HPP_
# define SRC_UTIL_LOGGER_HPP_

# include <iostream>
# include <sstream>
# include <map>

class Logger
{
	public:
		enum Level
		{
			LL_TRACE,
			LL_DEBUG,
			LL_INFO,
			LL_WARN,
			LL_ERROR,
			LL_FATAL,
			_LL_SIZE
		};

	private:
		static const std::string DEFAULT_TAG;
		static std::map<std::string, Logger*> INSTANCES;

	private:
		std::string m_tag;

	public:
		Logger(void);
		Logger(const std::string &tag);
		Logger(const Logger &other);

		virtual
		~Logger();

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
		log(Level level) const;

		const std::string&
		tag() const;

	public:
		static Logger&
		factory(const std::string &tag);

		static std::string
		levelToString(Level level);

		static void
		deleteAll(void);
};

#endif /* SRC_UTIL_LOGGER_HPP_ */
