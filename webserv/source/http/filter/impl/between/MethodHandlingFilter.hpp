/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodHandlingFilter.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:28:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 00:28:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODHANDLINGFILTER_HPP_
# define METHODHANDLINGFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class Logger;

class MethodHandlingFilter :
		public Filter,
		public Singleton<MethodHandlingFilter>
{
	public:
		static Logger &LOG;

	public:
		MethodHandlingFilter();
		MethodHandlingFilter(const MethodHandlingFilter &other);

		virtual
		~MethodHandlingFilter();

		MethodHandlingFilter&
		operator=(const MethodHandlingFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* METHODHANDLINGFILTER_HPP_ */
