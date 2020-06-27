/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TheReplacer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THEREPLACER_HPP
# define THEREPLACER_HPP

# include <string>
# include <fstream>

# ifndef DEBUG_REPLACER
#  define DEBUG_REPLACER 0
# endif

class TheReplacer
{
	private:
		std::string &_file;
		std::string &_s1;
		std::string &_s2;

		std::string _outFile;

		std::ifstream _in;
		std::ofstream _out;

		int _readInputFile(std::string &dest);
		int _writeOutputFile(std::string &src);
		void _closeStreams(void);

	public:
		TheReplacer(std::string &file, std::string &s1, std::string &s2);

		int replace();
};

#endif /* THEREPLACER_HPP_ */
