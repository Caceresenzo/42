/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IWritableBuffer.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:19:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/29 18:19:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IWRITABLEBUFFER_HPP_
# define IWRITABLEBUFFER_HPP_

#include <stddef.h>
#include <buffer/IBuffer.hpp>

class IWritableBuffer :
		public IBuffer
{
	public:
		virtual
		~IWritableBuffer(void);

		/**
		 * Store a character.
		 *
		 * @param c Character to store.
		 */
		virtual IWritableBuffer&
		store(char c) = 0;

		/**
		 * Store a string.
		 *
		 * @param str String to store.
		 */
		virtual IWritableBuffer&
		store(const std::string &str) = 0;

		/**
		 * Store a raw pointer.
		 *
		 * @param buffer Pointer to store.
		 * @param len Buffer size.
		 * @return Itself.
		 */
		virtual IWritableBuffer&
		store(const void *buffer, size_t len) = 0;

		/** @return Buffer's storage size. */
		virtual size_t
		size() const = 0;

		/** Clear the buffer's storage. */
		virtual void
		clear() = 0;
};

#endif /* IWRITABLEBUFFER_HPP_ */
