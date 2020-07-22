/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:30:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:30:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NINJATRAP_HPP_
# define NINJATRAP_HPP_

# include <string>

# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"

class NinjaTrap : public ClapTrap
{
	private:
		void doNinjaShoebox(std::string type, int index, ClapTrap *clapTrapPtr);

	protected:
		virtual std::ostream& says();

	public:
		NinjaTrap(void);
		NinjaTrap(std::string name);
		NinjaTrap(const NinjaTrap &other);

		virtual ~NinjaTrap(void);

		NinjaTrap &operator =(const NinjaTrap &right);

		void ninjaShoebox(FragTrap &target);
		void ninjaShoebox(ScavTrap &target);
		void ninjaShoebox(NinjaTrap &target);
		void ninjaShoebox(ClapTrap &target);
};

#endif /* NINJATRAP_HPP_ */
