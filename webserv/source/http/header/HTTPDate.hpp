/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPDate.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:26:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 12:26:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPDATE_HPP_
# define HTTPDATE_HPP_

#include <util/Time.hpp>
#include <string>

# define HTTPDATE_FORMAT "%a, %d %b %Y %H:%M:%S GMT"

class HTTPDate
{
	private:
		Time m_time;

	public:
		HTTPDate(void);
		HTTPDate(Time time);
		HTTPDate(const HTTPDate &other);

		virtual
		~HTTPDate(void);

		HTTPDate&
		operator=(const HTTPDate &other);

		std::string
		format(void) const;

		Time
		time(void) const;

	public:
		static HTTPDate
		now(void);
};

#endif /* HTTPDATE_HPP_ */
