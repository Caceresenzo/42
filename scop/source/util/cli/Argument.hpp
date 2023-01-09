/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Argument.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 00:56:42 by ecaceres          #+#    #+#             */
/*   Updated: 2022/11/14 00:56:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENT_HPP_
# define ARGUMENT_HPP_

# include <string>

class Argument
{
	private:
		std::string m_name;
		bool m_optional;
		std::string m_description;

	public:
		Argument(std::string name, bool optional);
		Argument(std::string name, bool optional, std::string description);

		virtual
		~Argument();

	public:
		std::string
		format_name() const;

	public:
		inline const std::string&
		name() const
		{
			return (m_name);
		}

		inline bool
		optional() const
		{
			return (m_optional);
		}

		inline const std::string&
		description() const
		{
			return (m_description);
		}
};

#endif /* ARGUMENT_HPP_ */
