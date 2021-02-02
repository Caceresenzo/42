/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Collections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:03:20 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 22:03:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTIONS_HPP_
# define COLLECTIONS_HPP_

#include <list>
#include <map>

class Collections
{
	private:
		Collections(void);
		Collections(const Collections &other);

		~Collections(void);

		Collections
		operator =(const Collections &other);

	public:
		template<typename K, typename V>
			static std::list<V>
			values(std::map<K, V> &map)
			{
				typename std::map<K, V>::iterator it = map.begin();
				typename std::map<K, V>::iterator ite = map.end();

				std::list<V> out;
				while (it != ite)
				{
					out.push_back(it->second);
					it++;
				}

				return (out);
			}

		template<typename K, typename V>
			static std::list<V>
			values(const std::map<K, V> &map)
			{
				typename std::map<K, V>::const_iterator it = map.begin();
				typename std::map<K, V>::const_iterator ite = map.end();

				std::list<V> out;
				while (it != ite)
				{
					out.push_back(it->second);
					it++;
				}

				return (out);
			}

		template<typename K, typename V>
			static void
			remove(std::map<K, V> &map, const K &key)
			{
				typename std::map<K, V>::iterator it = map.find(key);
				if (it != map.end())
					map.erase(it);
			}
};

#endif /* COLLECTIONS_HPP_ */
