/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functional.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:44:07 by ecaceres          #+#    #+#             */
/*   Updated: 2021/02/03 12:44:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONAL_H
# define FUNCTIONAL_H

namespace ft
{
	template<class T>
		struct less
		{
			public:
				bool
				operator()(const T &lhs, const T &rhs) const
				{
					return (lhs < rhs);
				}
		};

	template<class T>
		struct greater
		{
			public:
				bool
				operator()(const T &lhs, const T &rhs) const
				{
					return (lhs > rhs);
				}
		};

	template<class T>
		struct equal_to
		{
			public:
				bool
				operator()(const T &lhs, const T &rhs) const
				{
					return (lhs == rhs);
				}
		};
}

#endif
