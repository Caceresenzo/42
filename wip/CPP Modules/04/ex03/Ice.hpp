/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:38:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:38:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP_
# define ICE_HPP_

# include "AMateria.hpp"

class Ice : public AMateria
{
	public:
		Ice();
		Ice(const Ice &other);

		virtual ~Ice();

		Ice& operator=(const Ice &other);

		virtual AMateria* clone() const;
		virtual void use(ICharacter &target);
};

#endif /* ICE_HPP_ */
