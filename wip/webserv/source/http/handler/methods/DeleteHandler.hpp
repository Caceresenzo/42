/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 18:13:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 18:13:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETEHANDLER_HPP_
# define DELETEHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <util/Singleton.hpp>

class DeleteHandler :
		public HTTPMethodHandler,
		public Singleton<DeleteHandler>
{
	public:
		DeleteHandler();
		DeleteHandler(const DeleteHandler &other);

		virtual
		~DeleteHandler();

		DeleteHandler&
		operator =(const DeleteHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* DELETEHANDLER_HPP_ */
