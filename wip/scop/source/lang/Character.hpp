/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 22:10:43 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 22:10:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

class Character
{
	public:
		static char
		to_upper_case(char character);

		static bool
		is_upper_case(char character);

		static char
		to_lower_case(char character);

		static bool
		is_lower_case(char character);

		static bool
		is_digit(char character);
};

#endif /* CHARACTER_HPP_ */
