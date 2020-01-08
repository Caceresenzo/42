/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:03:20 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:03:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP_
# define CLAPTRAP_HPP_

# include <string>

class ClapTrap
{
	protected:
		long _hitPoints, _maxHitPoints;
		long _energyPoints, _maxEnergyPoints;
		long _level;
		std::string _name;
		long _meleeAttackDamage;
		long _rangedAttackDamage;
		long _armorDamageReduction;

	public:
		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &other);

		~ClapTrap(void);

		ClapTrap &operator =(const ClapTrap &right);

		void rangedAttack(std::string const &target);
		void meleeAttack(std::string const &target);

		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		std::string getName(void);
};

#endif /* CLAPTRAP_HPP_ */
