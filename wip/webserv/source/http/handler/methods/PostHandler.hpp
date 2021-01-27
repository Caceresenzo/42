/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 10:43:31 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/25 10:43:31 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTHANDLER_HPP_
# define POSTHANDLER_HPP_

#include <http/handler/HTTPMethodHandler.hpp>
#include <io/File.hpp>
#include <util/Singleton.hpp>

class PostHandler :
		public HTTPMethodHandler,
		public Singleton<PostHandler>
{
	public:
		PostHandler();
		PostHandler(const PostHandler &other);

		virtual
		~PostHandler();

		PostHandler&
		operator =(const PostHandler &other);

		bool
		handle(HTTPClient &client, HTTPRequest &request, HTTPResponse &response);
};

#endif /* PostHANDLER_HPP_ */
