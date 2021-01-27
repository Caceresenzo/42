/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodFilter.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:16:46 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 19:16:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODFILTER_HPP_
# define METHODFILTER_HPP_

#include <config/block/LocationBlock.hpp>
#include <http/filter/Filter.hpp>
#include <util/Optional.hpp>
#include <util/Singleton.hpp>

class HTTPMethod;
class ServerBlock;

class MethodFilter :
		public Filter,
		public Singleton<MethodFilter>
{
	public:
		MethodFilter();
		MethodFilter(const MethodFilter &other);

		virtual
		~MethodFilter();

		MethodFilter&
		operator=(const MethodFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);

	public:
		static bool
		isAcceptable(const Optional<const ServerBlock*> &serverBlock, const Optional<const LocationBlock*> &locationBlock, const HTTPMethod &method);

		static long
		maxBodySizeFor(const Optional<const ServerBlock*> &serverBlock, const Optional<const LocationBlock*> &locationBlock);

};

#endif /* METHODFILTER_HPP_ */
