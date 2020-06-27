/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIEEVENT_HPP
# define ZOMBIEEVENT_HPP

# include <string>

# include "Zombie.hpp"

class ZombieEvent
{
	private:
		std::string _type;

	public:
		static std::string NAMES[];

		ZombieEvent(void);

		void setZombieType(std::string type);

		Zombie *newZombie(std::string name);
		Zombie *randomChump(void);
};

#endif /* ZOMBIEEVENT_HPP_ */
