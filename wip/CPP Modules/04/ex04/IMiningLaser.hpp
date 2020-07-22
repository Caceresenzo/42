/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMiningLaser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:43:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:43:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMININGLASER_HPP_
# define IMININGLASER_HPP_

# include "IAsteroid.hpp"

class IMiningLaser
{
	public:
		virtual ~IMiningLaser() { }

		virtual void mine(IAsteroid*) = 0;
};

#endif /* IMININGLASER_HPP_ */
