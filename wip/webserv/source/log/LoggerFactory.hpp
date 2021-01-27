/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LoggerFactory.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:06:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 16:06:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGERFACTORY_HPP_
# define LOGGERFACTORY_HPP_

#include <log/Logger.hpp>
#include <map>
#include <string>

class LoggerFactory
{
	public:
		typedef std::map<std::string, Logger*> logger_map;
		typedef logger_map::iterator iterator;

	private:
		static logger_map &getStorage();

	public:
		static Logger&
		get(const std::string &tag);

		static void
		destroy(void);
};

#endif /* LOGGERFACTORY_HPP_ */
