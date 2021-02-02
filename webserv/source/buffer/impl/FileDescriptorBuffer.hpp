/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptorBuffer.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:24:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/17 18:24:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORBUFFER_HPP_
# define FILEDESCRIPTORBUFFER_HPP_

#include <io/FileDescriptor.hpp>
#include <stddef.h>
#include <sys/types.h>
#include <buffer/impl/BaseBuffer.hpp>
#include <string>

class FileDescriptorBuffer :
		public BaseBuffer,
		public Closable
{
	public:
		enum ActionOnDestructorMode
		{
			NOTHING/**/= 0b00,
			CLOSE/*  */= 0b01,
			DELETE/* */= 0b10,
		};

	protected:
		FileDescriptor &m_fd;
		int m_actionOnDestroy;
		bool m_readEverything;

	public:
		FileDescriptorBuffer(void);
		FileDescriptorBuffer(const FileDescriptorBuffer &other);

		FileDescriptorBuffer&
		operator =(const FileDescriptorBuffer &other);

	protected:
		FileDescriptorBuffer(FileDescriptor &fileDescriptor, int actionOnDestroy, size_type maxSize);
		// FileDescriptorBuffer(FileDescriptor &fileDescriptor, const std::string body, int actionOnDestroy, size_type maxSize);

	public:
		virtual
		~FileDescriptorBuffer();

		ssize_t
		read(size_t len = 32768);

		ssize_t
		write(size_t len = 32768);

		void
		close(void);

		inline bool
		hasReadEverything() const
		{
			return (m_readEverything);
		}

		inline FileDescriptor&
		descriptor(void)
		{
			return (m_fd);
		}

		inline const FileDescriptor&
		descriptor(void) const
		{
			return (m_fd);
		}
		
		ssize_t
		storeZeros(size_t size);

	public:
		static FileDescriptorBuffer*
		from(FileDescriptor &fileDescriptor, int actionOnDestroy = CLOSE, size_type maxSize = std::string::npos);
};

#endif /* FILEDESCRIPTORBUFFER_HPP_ */
