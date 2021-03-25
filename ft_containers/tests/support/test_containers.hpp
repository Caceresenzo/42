/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_containers.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 17:08:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 17:08:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_CONTAINERS_HPP_
# define TEST_CONTAINERS_HPP_

# ifndef TEST_USE_STD
#  define TEST_USE_STD 0
# endif

# ifndef NOTIFY_WHICH
#  define NOTIFY_WHICH 0
# endif

# if NOTIFY_WHICH
#  if TEST_USE_STD
#   warning USING STD
#  else
#   warning USING 42
#  endif
# endif

#endif /* TEST_CONTAINERS_HPP_ */
