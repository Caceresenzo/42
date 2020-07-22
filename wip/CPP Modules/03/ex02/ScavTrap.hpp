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

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	protected:
		virtual std::ostream& says();

	public:
		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap &other);

		virtual ~ScavTrap(void);

		ScavTrap &operator =(const ScavTrap &right);

		void challengeNewcomer(std::string const &target);
};

#endif /* SCAVTRAP_HPP */
