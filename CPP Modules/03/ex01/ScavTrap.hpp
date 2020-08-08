/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:55:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:55:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include <string>

class ScavTrap
{
	private:
		long _hitPoints, _maxHitPoints;
		long _energyPoints, _maxEnergyPoints;
		long _level;
		std::string _name;
		long _meleeAttackDamage;
		long _rangedAttackDamage;
		long _armorDamageReduction;

	protected:
		std::ostream& says();
		std::ostream& says(std::string msg);

	public:
		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap &other);

		~ScavTrap(void);

		ScavTrap &operator =(const ScavTrap &right);

		void rangedAttack(std::string const &target);
		void meleeAttack(std::string const &target);

		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		void challengeNewcomer(std::string const &target);
};

#endif /* SCAVTRAP_HPP */
