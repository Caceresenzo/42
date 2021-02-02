/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LogLevel.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:09:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 16:09:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGLEVEL_HPP_
# define LOGLEVEL_HPP_

#include <util/Enum.hpp>
#include <iostream>

class LogLevel :
		public Enum<LogLevel>
{
	private:
		int m_color;

	public:
		LogLevel(int color);

		int
		color() const;

	public:
		static const LogLevel *TRACE;
		static const LogLevel *DEBUG;
		static const LogLevel *INFO;
		static const LogLevel *WARN;
		static const LogLevel *ERROR;
		static const LogLevel *FATAL;

		static const LogLevel *ACTIVE;
		static bool COLORED;
		static std::ostream *OUTPUT;
};

#endif /* LOGLEVEL_HPP_ */
