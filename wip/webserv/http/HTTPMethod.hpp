/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 17:32:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 17:32:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMETHOD_HPP_
# define HTTPMETHOD_HPP_

# include <iostream>
# include <vector>

class HTTPMethod
{
	private:
		std::string m_name;

		static std::vector<HTTPMethod> s_DEFAULTS;

	public:
		HTTPMethod(void);
		HTTPMethod(const std::string &name);
		HTTPMethod(const HTTPMethod &other);

		HTTPMethod&
		operator =(const HTTPMethod &other);

		const std::string&
		name(void) const;

		static void
		loadDefaults(void);

		static const std::vector<HTTPMethod>&
		defaults(void);
};

std::ostream&
operator <<(std::ostream &stream, const HTTPMethod &method);

#endif /* HTTPMETHOD_HPP_ */
