/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StripMiner.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:50:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:50:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRIPMINER_HPP_
# define STRIPMINER_HPP_

# include "IMiningLaser.hpp"

class StripMiner : public IMiningLaser
{
	public:
		StripMiner();
		StripMiner(const StripMiner &other);

		virtual ~StripMiner();

		StripMiner& operator=(const StripMiner &other);

		virtual void mine(IAsteroid*);
};

#endif /* STRIPMINER_HPP_ */
