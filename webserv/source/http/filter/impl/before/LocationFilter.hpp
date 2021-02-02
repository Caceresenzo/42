/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationFilter.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:10:43 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 19:10:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONFILTER_HPP_
# define LOCATIONFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class Logger;

class LocationFilter :
		public Filter, public Singleton<LocationFilter>
{
	public:
		static Logger &LOG;

	public:
		LocationFilter();
		LocationFilter(const LocationFilter &other);

		virtual
		~LocationFilter();

		LocationFilter&
		operator=(const LocationFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* LOCATIONFILTER_HPP_ */
