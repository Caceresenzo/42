/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMutant.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:40:57 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 17:40:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPERMUTANT_HPP_
# define SUPERMUTANT_HPP_

# include "Enemy.hpp"

class SuperMutant : public Enemy
{
	public:
		SuperMutant();
		SuperMutant(const SuperMutant &other);

		virtual ~SuperMutant();

		SuperMutant& operator=(const SuperMutant &other);

		virtual void takeDamage(int);
};

#endif /* SUPERMUTANT_HPP_ */
