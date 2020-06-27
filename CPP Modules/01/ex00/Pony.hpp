/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONY_HPP
# define PONY_HPP

# include <string>

typedef enum {
	c_nocolor = -255,
	c_white = 0,
	c_brown,
	c_black
} t_color;

class Pony
{
	private:
		std::string name;
		t_color color;

	public:
		Pony(std::string name, t_color color);
		~Pony(void);

		void tellName(void);
		void changeColor(t_color newColor);
		void tellColor(void);
};

#endif /* PONY_HPP_ */
