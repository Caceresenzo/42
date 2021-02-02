/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefaultPageManager.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 19:54:36 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/24 19:54:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTPAGES_HPP_
# define DEFAULTPAGES_HPP_

#include <util/Singleton.hpp>
#include <map>
#include <string>

class HTTPStatus;
class RootBlock;
class ServerBlock;

class DefaultPages :
		public Singleton<DefaultPages>
{
	public:
		typedef std::map<int, std::string> cache_map;
		typedef cache_map::iterator iterator;

	private:
		cache_map m_cache;

	private:
		DefaultPages(const DefaultPages &other);

		DefaultPages&
		operator =(const DefaultPages &other);

	public:
		DefaultPages();

	public:
		virtual
		~DefaultPages();

		const std::string&
		resolve(const HTTPStatus &httpStatus);
};

#endif /* DEFAULTPAGES_HPP_ */
