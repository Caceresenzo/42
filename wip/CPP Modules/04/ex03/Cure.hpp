/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:38:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:38:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP_
# define CURE_HPP_

# include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure();
		Cure(const Cure &other);

		virtual ~Cure();

		Cure& operator=(const Cure &other);

		virtual AMateria* clone() const;
		virtual void use(ICharacter &target);
};

#endif /* CURE_HPP_ */
