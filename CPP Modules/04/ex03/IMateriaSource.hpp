/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:58:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:58:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMATERIASOURCE_HPP_
# define IMATERIASOURCE_HPP_

#include <iostream>

#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() { }

		virtual void learnMateria(AMateria*) = 0;

		virtual AMateria* createMateria(std::string const &type) = 0;
};

#endif /* IMATERIASOURCE_HPP_ */
