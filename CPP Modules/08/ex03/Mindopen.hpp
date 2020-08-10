/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mindopen.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:17:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 14:17:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINDOPEN_HPP_
# define MINDOPEN_HPP_

# if defined(BRAINFUCK_CHARSET) and BRAINFUCK_CHARSET
#  define MO_INCREMENT_DATA '>'
#  define MO_DECREMENT_DATA '<'
#  define MO_INCREMENT '+'
#  define MO_DECREMENT '-'
#  define MO_OUTPUT '.'
#  define MO_INPUT ','
#  define MO_WHILE_OPEN '['
#  define MO_WHILE_CLOSE ']'
# else
#  define MO_INCREMENT_DATA 'D'
#  define MO_DECREMENT_DATA 'd'
#  define MO_INCREMENT 'I'
#  define MO_DECREMENT 'i'
#  define MO_OUTPUT 'O'
#  define MO_INPUT 'o'
#  define MO_WHILE_OPEN '{'
#  define MO_WHILE_CLOSE '}'
# endif

#endif /* MINDOPEN_HPP_ */
