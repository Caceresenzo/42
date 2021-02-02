/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InetAddress.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 20:45:04 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/18 20:45:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INETADDRESS_HPP_
# define INETADDRESS_HPP_

#include <util/Byte.hpp>
#include <string>
#include <vector>

class InetAddress
{
	public:
		virtual
		~InetAddress();

		virtual std::vector<byte>
		address() const = 0;

		virtual std::string
		hostAddress() const = 0;

		virtual InetAddress*
		clone() const = 0;
};

#endif /* INETADDRESS_HPP_ */
