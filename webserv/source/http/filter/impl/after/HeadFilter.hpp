/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeadFilter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 00:35:58 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 00:35:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADFILTER_HPP_
# define HEADFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class HeadFilter :
		public Filter,
		public Singleton<HeadFilter>
{
	public:
		HeadFilter();
		HeadFilter(const HeadFilter &other);

		virtual
		~HeadFilter();

		HeadFilter&
		operator=(const HeadFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* HEADFILTER_HPP_ */
