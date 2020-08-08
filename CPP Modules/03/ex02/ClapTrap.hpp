/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:55:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:55:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>

class ClapTrap
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
		virtual std::ostream& says();
		std::ostream& saysm(std::string msg);

	public:
		ClapTrap(void);
		ClapTrap(long hitPoints, long maxHitPoints, long energyPoints, long maxEnergyPoints, long level, std::string name, long meleeAttackDamage, long rangedAttackDamage, long armorDamageReduction);
		ClapTrap(const ClapTrap &other);

		virtual ~ClapTrap(void);

		ClapTrap &operator =(const ClapTrap &right);

		void rangedAttack(std::string const &target);
		void meleeAttack(std::string const &target);

		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
		
		long& getEnergyPoints();
		long& getHitPoints();
		const std::string& getName();
};

#endif /* CLAPTRAP_HPP */
