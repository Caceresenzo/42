/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_std.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:42:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 17:42:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPPORT_STD_HPP_
# define SUPPORT_STD_HPP_

# include "test_containers.hpp"

# if TEST_USE_STD
#  include <iterator>
#  include <algorithm>
#  define DISTANCE std::distance
#  define SWAP std::swap
#  define NEXT std::next
#  define PREV ft::prev
#  define RANDOM_ACCESS_ITERATOR_TAG std::random_access_iterator_tag
#  define ITERATOR_TRAITS std::iterator_traits
#  define PAIR std::pair

namespace std {
	template<typename Iterator>
		Iterator
		next(Iterator iterator, unsigned long n = 1)
		{
			while (n--)
				++iterator;
			return (iterator);
		}

	template<typename Iterator>
		Iterator
		prev(Iterator iterator, unsigned long n = 1)
		{
			while (n--)
				--iterator;
			return (iterator);
		}
}

# else
#  include <Iterator.hpp>
#  include <Algorithm.hpp>
#  define DISTANCE ft::distance
#  define SWAP ft::swap
#  define NEXT ft::next
#  define PREV ft::prev
#  define RANDOM_ACCESS_ITERATOR_TAG ft::random_access_iterator_tag
#  define ITERATOR_TRAITS ft::iterator_traits
#  define PAIR ft::pair
# endif

#endif /* SUPPORT_STD_HPP_ */
