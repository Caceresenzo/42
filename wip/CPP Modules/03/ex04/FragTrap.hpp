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

# include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
	private:
		std::string _vaulthunterAttacks[5];
		long _vaulthunterDamages[5];

	public:
		FragTrap(void);
		FragTrap(std::string name);
		FragTrap(const FragTrap &other);

		~FragTrap(void);

		FragTrap &operator =(const FragTrap &right);

		void rangedAttack(std::string const &target);
		void meleeAttack(std::string const &target);

		void vaulthunter_dot_exe(std::string const &target);
};

#endif /* FRAGTRAP_HPP_ */
