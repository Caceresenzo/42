/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketBuffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 22:38:35 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 22:38:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETBUFFER_HPP_
# define SOCKETBUFFER_HPP_

#include <io/Socket.hpp>
#include <stddef.h>
#include <sys/types.h>
#include <buffer/impl/FileDescriptorBuffer.hpp>
#include <string>

class SocketBuffer :
		public FileDescriptorBuffer
{
	private:
		SocketBuffer(void);
		SocketBuffer(const SocketBuffer &other);

		SocketBuffer&
		operator =(const SocketBuffer &other);

	protected:
		SocketBuffer(Socket &socket, int actionOnDestroy, size_type maxSize);

	public:
		virtual
		~SocketBuffer();

		ssize_t
		recv(int flags = 0, size_t len = 32768);

		ssize_t
		send(int flags = 0, size_t len = 32768);

	public:
		static SocketBuffer*
		from(Socket &socket, int actionOnDestroy = FileDescriptorBuffer::CLOSE, size_type maxSize = std::string::npos);
};

#endif /* SOCKETBUFFER_HPP_ */
