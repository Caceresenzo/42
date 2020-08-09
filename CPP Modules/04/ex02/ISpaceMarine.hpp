/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISpaceMarine.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:13:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:13:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISPACEMARINE_HPP_
# define ISPACEMARINE_HPP_

class ISpaceMarine
{
	public:
		virtual ~ISpaceMarine() {}

		virtual ISpaceMarine* clone() const = 0;

		virtual void battleCry() const = 0;
		virtual void rangedAttack() const = 0;
		virtual void meleeAttack() const = 0;
};

#endif /* ISPACEMARINE_HPP_ */
