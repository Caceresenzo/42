/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerFilter.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:03:57 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 19:03:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERFILTER_HPP_
# define SERVERFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class HTTPClient;
class ServerBlock;

class ServerFilter :
		public Filter, public Singleton<ServerFilter>
{
	public:
		ServerFilter();
		ServerFilter(const ServerFilter &other);

		virtual
		~ServerFilter();

		ServerFilter&
		operator=(const ServerFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);

		static ServerBlock const*
		findBlock(HTTPClient &client);
};

#endif /* SERVERFILTER_HPP_ */
