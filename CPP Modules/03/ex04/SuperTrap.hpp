/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    SuperTrap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:52:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPERTRAP_HPP_
# define SUPERTRAP_HPP_

# include <string>

# include "FragTrap.hpp"
# include "NinjaTrap.hpp"

class SuperTrap : public FragTrap, public NinjaTrap
{
	protected:
		virtual std::ostream& says();

	public:
		SuperTrap(void);
		SuperTrap(std::string name);
		SuperTrap(SuperTrap const &other);

		virtual ~SuperTrap(void);

		SuperTrap &operator =(const SuperTrap &right);
};

#endif /* SUPERTRAP_HPP_ */
