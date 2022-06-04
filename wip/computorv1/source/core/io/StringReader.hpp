/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringReader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:12:08 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/04 20:12:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGREADER_HPP_
# define STRINGREADER_HPP_

#include <string>

class StringReader
{
	public:
		static const char END_OF_CONTENT;

	private:
		std::string m_string;
		std::string::size_type m_start;
		std::string::size_type m_end;
		std::string::size_type m_index;

	public:
		StringReader(const std::string &string);
		StringReader(const std::string &string, std::string::size_type start, std::string::size_type end);
		StringReader(const StringReader &other);

	public:
		char
		read(void);

		char
		peek(std::string::size_type n = 0) const;

		StringReader&
		skip(std::string::size_type n = 1);

		StringReader&
		skip_whitespaces(void);

		bool
		is_end_of_content(void) const;

		std::string::size_type
		get_index(void) const;

	private:
		bool
		is_end_of_file_at_index(std::string::size_type index) const;

		std::string::size_type
		increment(std::string::size_type n) const;

		char
		at(std::string::size_type index) const;
};

#endif /* STRINGREADER_HPP_ */
