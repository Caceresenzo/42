/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:16:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:16:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUAD_HPP_
# define SQUAD_HPP_

# include "ISquad.hpp"

class Squad : public ISquad
{
	private:
		int _size;
		ISpaceMarine **_array;

	public:
		Squad();
		Squad(const Squad &other);

		virtual ~Squad();

		Squad& operator=(const Squad &other);

		virtual int getCount() const;
		virtual ISpaceMarine* getUnit(int) const;
		virtual int push(ISpaceMarine*);
};

#endif /* SQUAD_HPP_ */
