/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IndexFilter.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:46:45 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 23:46:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEXFILTER_HPP_
# define INDEXFILTER_HPP_

#include <http/filter/Filter.hpp>
#include <util/Singleton.hpp>

class IndexFilter :
		public Filter,
		public Singleton<IndexFilter>
{
	public:
		IndexFilter();
		IndexFilter(const IndexFilter &other);

		virtual
		~IndexFilter();

		IndexFilter&
		operator=(const IndexFilter &other);

		void
		doFilter(HTTPClient &client, HTTPRequest &request, HTTPResponse &response, FilterChain &next);
};

#endif /* INDEXFILTER_HPP_ */
