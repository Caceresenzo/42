/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:29:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/16 16:26:57 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_HPP_
# define OPTION_HPP_

# include <string>

class Option
{
	private:
		char m_short;
		std::string m_long;
		std::string m_description;
		std::string m_argument_name;

	private:
		Option(void);
		Option(const Option &other);

		Option&
		operator=(const Option &other);

	public:
		Option(char short_name, const std::string &long_name, const std::string &description);
		Option(char short_name, const std::string &long_name, const std::string &description, const std::string &argument_name);

		virtual
		~Option(void);

		inline char
		short_name(void) const
		{
			return (m_short);
		}

		inline const std::string&
		long_name(void) const
		{
			return (m_long);
		}

		inline const std::string&
		description(void) const
		{
			return (m_description);
		}

		inline bool
		has_argument(void) const
		{
			return (!m_argument_name.empty());
		}

		inline const std::string&
		argument_name(void) const
		{
			return (m_argument_name);
		}
};

#endif /* OPTION_HPP_ */
