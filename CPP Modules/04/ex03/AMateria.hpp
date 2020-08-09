/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:20:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:20:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP_
# define AMATERIA_HPP_

# include <iostream>

class ICharacter;

class AMateria
{
	private:
		std::string _type;
		unsigned int _xp;

	protected:
		AMateria();

	public:
		AMateria(std::string const &type);
		AMateria(const AMateria &other);

		virtual ~AMateria();

		AMateria& operator=(const AMateria &other);

		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter &target);

		std::string const& getType() const;
		unsigned int getXp() const;
};

# include "ICharacter.hpp"

#endif /* AMATERIA_HPP_ */
