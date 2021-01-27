/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FinalFilter.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 01:19:41 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 01:19:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINALFILTER_HPP_
# define FINALFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class FinalFilter :
		public Filter,
		public Singleton<FinalFilter>
{
	public:
		FinalFilter();
		FinalFilter(const FinalFilter &other);

		virtual
		~FinalFilter();

		FinalFilter&
		operator=(const FinalFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* FINALFILTER_HPP_ */
