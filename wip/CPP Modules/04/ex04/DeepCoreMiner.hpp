/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeepCoreMiner.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:50:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:50:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEEPCOREMINER_HPP_
# define DEEPCOREMINER_HPP_

# include "IMiningLaser.hpp"

class DeepCoreMiner : public IMiningLaser
{
	public:
		DeepCoreMiner();
		DeepCoreMiner(const DeepCoreMiner &other);

		virtual ~DeepCoreMiner();

		DeepCoreMiner& operator=(const DeepCoreMiner &other);

		virtual void mine(IAsteroid*);
};

#endif /* DEEPCOREMINER_HPP_ */
