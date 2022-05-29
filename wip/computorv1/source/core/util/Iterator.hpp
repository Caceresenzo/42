/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:56:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 23:56:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP_
# define ITERATOR_HPP_

class Iterator
{
	public:
		template<typename I>
			static I
			next(I iterator)
			{
				iterator++;
				return (iterator);
			}
};

#endif /* ITERATOR_HPP_ */
