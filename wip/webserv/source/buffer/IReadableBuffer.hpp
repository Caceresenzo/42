/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IReadableBuffer.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:19:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/29 18:19:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IREADABLEBUFFER_HPP_
# define IREADABLEBUFFER_HPP_

#include <stddef.h>
#include <buffer/IBuffer.hpp>

class IReadableBuffer :
		public IBuffer
{
	public:
		virtual
		~IReadableBuffer(void);

		/**
		 * Consume a character.
		 *
		 * @param c Where to store the result to.
		 * @return Whether or not a character has been consumed.
		 */
		virtual bool
		next(char &c) = 0;

		/**
		 * Peek the next character.
		 *
		 * @param c Where to store the result to.
		 * @param index Peek the next x character. (default is 0)
		 * @return Whether or not the character have been peeked.
		 */
		virtual bool
		peek(char &c, size_t index = 0) const = 0;

		/**
		 * Consume a whole line.
		 *
		 * @param str Where to store the result to.
		 * &param crlf If the line end with a \r\n.
		 * @return Whether or not the line has been consumed.
		 */
		virtual bool
		next(std::string &str, bool crlf = false) = 0;

		/**
		 * Skip the next n byte in the buffer.
		 *
		 * @param n Number of byte to skip.
		 * @return If there is still data remaining after the skip.
		 */
		virtual bool
		skip(size_t n) = 0;
};

#endif /* IREADABLEBUFFER_HPP_ */
