/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:46:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:46:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

# include "ICharacter.hpp"

# define INVENTORY_SIZE 4

class Character : public ICharacter
{
	private:
		std::string _name;
		AMateria *_inventory[INVENTORY_SIZE];

		void zeroInventory();

	protected:
		Character();

	public:
		Character(std::string name);
		Character(const Character &other);

		virtual ~Character();

		Character& operator=(const Character &other);

		virtual std::string const& getName() const;

		virtual void equip(AMateria *materia);

		virtual void unequip(int index);

		virtual void use(int index, ICharacter &target);
};

#endif /* CHARACTER_HPP_ */
