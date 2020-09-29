/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:03:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 18:03:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_VECTOR_HPP_
# define UNIT_VECTOR_HPP_

# include "test_macros.hpp"
# include "test_containers.hpp"

# include <Iterator.hpp>

# if TEST_USE_STD
#  include <vector>
#  define VECTOR std::vector

template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, std::input_iterator_tag)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;

		while (first != last)
		{
			++first;
			++result;
		}

		return (result);
	}

template<class It>
	typename ft::iterator_traits<It>::difference_type
	do_distance(It first, It last, std::random_access_iterator_tag)
	{
		return (last - first);
	}

# else
#  include <Vector.hpp>
#  define VECTOR ft::Vector
# endif

#endif /* UNIT_VECTOR_HPP_ */
