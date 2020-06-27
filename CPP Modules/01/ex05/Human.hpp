/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_HPP
# define HUMAN_HPP

# include <string>

# include "Brain.hpp"

class Human
{
	private:
		const Brain _brain;

	public:
		/* 'const' at the end: the method will never try to modify the object. */
		std::string identify(void) const;

		/* return a 'const': the returned variable is a const too. */
		const Brain& getBrain(void) const;
};

#endif /* HUMAIN_HPP_ */
