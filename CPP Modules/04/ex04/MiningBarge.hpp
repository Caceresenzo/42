/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiningBarge.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:07:39 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 15:07:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MININGBARGE_HPP_
# define MININGBARGE_HPP_

# include "IAsteroid.hpp"
# include "IMiningLaser.hpp"

# define INVENTORY_SIZE 4

class MiningBarge
{
	private:
		IMiningLaser *_inventory[INVENTORY_SIZE];

		void zeroInventory();

	public:
		MiningBarge();
		MiningBarge(const MiningBarge &other);

		virtual ~MiningBarge();

		MiningBarge& operator=(const MiningBarge &other);

		void equip(IMiningLaser*);
		void mine(IAsteroid*) const;
};

#endif /* MININGBARGE_HPP_ */
