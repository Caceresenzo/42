/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:02:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 18:02:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

# include <iostream>

# include "AWeapon.hpp"
# include "Enemy.hpp"

# define DEFAULT_MAX_AP 40

class Character
{
	private:
		std::string _name;
		int _ap;
		AWeapon *_weapon;

	protected:
		Character();

	public:
		Character(std::string const &name);
		Character(const Character &other);

		virtual ~Character();

		Character& operator=(const Character &other);

		void recoverAP();
		void equip(AWeapon*);
		void attack(Enemy*);

		const std::string& getName() const;
		int getAp() const;
		AWeapon* getWeapon() const;
};

std::ostream& operator <<(std::ostream &stream, Character &character);

#endif /* CHARACTER_HPP_ */
