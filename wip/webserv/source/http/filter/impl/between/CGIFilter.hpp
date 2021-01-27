/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIFilter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:27:23 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 00:27:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIFILTER_HPP_
# define CGIFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class Logger;

class CGIFilter :
		public Filter,
		public Singleton<CGIFilter>
{
	public:
		static Logger &LOG;

	public:
		CGIFilter();
		CGIFilter(const CGIFilter &other);

		virtual
		~CGIFilter();

		CGIFilter&
		operator=(const CGIFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* CGIFILTER_HPP_ */
