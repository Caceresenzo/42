/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:03:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 18:03:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_LIST_HPP_
# define UNIT_LIST_HPP_

# include "test_macros.hpp"
# include "test_containers.hpp"
# include "support_std.hpp"

# if TEST_USE_STD
#  include <list>
#  define LIST std::list
# else
#  include <List.hpp>
#  define LIST ft::List
# endif

#endif /* UNIT_LIST_HPP_ */
