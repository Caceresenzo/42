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

class FragTrap : public ClapTrap
{
	protected:
		virtual std::ostream& says();

	public:
		FragTrap(void);
		FragTrap(std::string name);
		FragTrap(const FragTrap &other);

		virtual ~FragTrap(void);

		FragTrap &operator =(const FragTrap &right);

		void vaulthunter_dot_exe(std::string const &target);
};

#endif /* FRAGTRAP_HPP_ */
