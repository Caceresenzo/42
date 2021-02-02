/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthenticationFilter.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:49:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 18:49:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTHENTICATIONFILTER_HPP_
# define AUTHENTICATIONFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class AuthenticationFilter :
		public Filter, public Singleton<AuthenticationFilter>
{
	public:
		AuthenticationFilter();
		AuthenticationFilter(const AuthenticationFilter &other);

		virtual
		~AuthenticationFilter();

		AuthenticationFilter&
		operator=(const AuthenticationFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* AUTHENTICATIONFILTER_HPP_ */
