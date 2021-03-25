/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Function.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 16:37:31 by ecaceres          #+#    #+#             */
/*   Updated: 2021/02/03 16:37:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

namespace ft
{
	template<typename _Arg1, typename _Arg2, typename _Result>
		struct binary_function
		{
				/** first_argument_type is the type of the first argument. */
				typedef _Arg1 first_argument_type;

				/** second_argument_type is the type of the second argument. */
				typedef _Arg2 second_argument_type;

				/**  result_type is the return type. */
				typedef _Result result_type;
		};
}

#endif /* FUNCTION_HPP_ */
