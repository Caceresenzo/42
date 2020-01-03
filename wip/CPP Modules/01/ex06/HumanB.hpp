/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanV.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>

# include "Weapon.hpp"

class HumanB
{
	private:
		std::string _name;
		Weapon *_weapon;

	public:
		HumanB(std::string name);

		void setWeapon(Weapon &weapon);
		void attack(void);
};

#endif /* HUMANB_HPP_ */
