/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

class Utils
{
	private:
		Utils(void);
		Utils(const Utils &other);

		~Utils(void);

		Utils &operator =(const Utils &other);

	public:
		static bool isOperator(char c);
		static bool isDigit(char c);
		static bool isParenthesis(char c);
		static bool isWhitespace(char c);
};

#endif /* UTILS_HPP_ */
