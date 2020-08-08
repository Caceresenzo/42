/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:55:33 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:55:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include <string>

class FragTrap
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
		FragTrap(void);
		FragTrap(std::string name);
		FragTrap(const FragTrap &other);

		~FragTrap(void);

		FragTrap &operator =(const FragTrap &right);

		void rangedAttack(std::string const &target);
		void meleeAttack(std::string const &target);

		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		void vaulthunter_dot_exe(std::string const &target);
};

#endif /* FRAGTRAP_HPP_ */
