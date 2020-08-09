/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:25:09 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:25:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICHARACTER_HPP_
# define ICHARACTER_HPP_

# include <iostream>

# include "AMateria.hpp"

class ICharacter
{
	public:
		virtual ~ICharacter() { }

		virtual std::string const& getName() const = 0;

		virtual void equip(AMateria *m) = 0;

		virtual void unequip(int idx) = 0;

		virtual void use(int idx, ICharacter &target) = 0;
};

#endif /* ICHARACTER_HPP_ */
