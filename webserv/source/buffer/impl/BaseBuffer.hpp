/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseBuffer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:24:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 22:24:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASEBUFFER_HPP_
# define BASEBUFFER_HPP_

#include <buffer/IReadableBuffer.hpp>
#include <buffer/IWritableBuffer.hpp>
#include <stddef.h>
#include <string>

class BaseBuffer :
		public IWritableBuffer,
		public IReadableBuffer
{
	public:
		typedef std::string
		(*transformer)(const std::string&);

		typedef std::string::size_type size_type;

	protected:
		std::string m_storage;
		size_type m_maxSize;

	private:
		BaseBuffer(const BaseBuffer &other);

		BaseBuffer&
		operator=(const BaseBuffer &other);

	public:
		BaseBuffer();
		BaseBuffer(size_type maxSize);
		BaseBuffer(const std::string &storage, size_type maxSize = std::string::npos);

		virtual
		~BaseBuffer();

		BaseBuffer&
		store(char c);

		BaseBuffer&
		store(const std::string &str);

		BaseBuffer&
		store(const void *buffer, size_t len);

		BaseBuffer&
		store(BaseBuffer &buffer, bool andErase = true, transformer = NULL);

		bool
		next(char &c);

		bool
		peek(char &c, size_t index = 0) const;

		bool
		next(std::string &str, bool crlf = false);

		bool
		skip(size_t n);

		size_t
		size() const;

		bool
		empty() const;

		void
		clear();

		size_t
		capacity() const;

		inline std::string&
		storage()
		{
			return (m_storage);
		}

		inline const std::string&
		storage() const
		{
			return (m_storage);
		}
};

#endif /* BASEBUFFER_HPP_ */
