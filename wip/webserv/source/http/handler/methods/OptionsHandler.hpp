/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionsHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:42:43 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:42:43 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONSHANDLER_HPP_
# define OPTIONSHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <util/Singleton.hpp>

class OptionsHandler :
		public HTTPMethodHandler,
		public Singleton<OptionsHandler>
{
	public:
		OptionsHandler();
		OptionsHandler(const OptionsHandler &other);

		virtual
		~OptionsHandler();

		OptionsHandler&
		operator =(const OptionsHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* OptionsHANDLER_HPP_ */
