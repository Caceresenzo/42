/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:34:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_CONFIG_BLOCK_CGI_HPP_
# define SRC_CONFIG_BLOCK_CGI_HPP_

#include <iostream>

class CGI
{
	public:
		std::string m_name;
		std::string m_path;

	public:
		CGI();
		virtual
		~CGI();
		CGI(const CGI &other);
		CGI&
		operator=(const CGI &other);
};

#endif /* SRC_CONFIG_BLOCK_CGI_HPP_ */
