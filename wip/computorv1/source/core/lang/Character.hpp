/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 23:04:22 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 23:04:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

class Character
{
	public:
		static bool
		is_digit(char chr);

		static bool
		is_whitespace(char chr);

		static char
		to_uppercase(char chr);
};

#endif /* CHARACTER_HPP_ */
