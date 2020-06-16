/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <fstream>

# define DEST_CONSOLE "console"
# define DEST_FILE "file"

class Logger
{
	private:
		std::string _file;
		std::ofstream _stream;

		std::string makeLogEntry(std::string const &msg);

		void logToConsole(std::string const &msg);
		void logToFile(std::string const &msg);

	public:
		Logger(std::string file);
		~Logger(void);

		void log(std::string const &dest, std::string const &message);
};

#endif /* LOGGER_HPP_ */
