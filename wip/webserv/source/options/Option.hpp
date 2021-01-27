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
		std::string m_argumentName;

	private:
		Option(void);
		Option(const Option &other);

		Option&
		operator=(const Option &other);

	public:
		Option(char shortName, std::string longName, std::string description);
		Option(char shortName, std::string longName, std::string description, std::string valueName);

		virtual
		~Option(void);

		char
		shortName(void) const;

		const std::string&
		longName(void) const;

		const std::string&
		description(void) const;

		bool
		hasArgument(void) const;

		const std::string&
		argumentName(void) const;
};

#endif /* OPTION_HPP_ */
