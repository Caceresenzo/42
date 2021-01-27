/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorFilter.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:30:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 00:30:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORFILTER_HPP_
# define ERRORFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class Logger;

class ErrorFilter :
		public Filter,
		public Singleton<ErrorFilter>
{
	public:
		static Logger &LOG;

	public:
		ErrorFilter();
		ErrorFilter(const ErrorFilter &other);

		virtual
		~ErrorFilter();

		ErrorFilter&
		operator=(const ErrorFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* ERRORFILTER_HPP_ */
