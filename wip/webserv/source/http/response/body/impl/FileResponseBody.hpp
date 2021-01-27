/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileResponseBody.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:14:47 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 17:14:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILERESPONSEBODY_HPP_
# define FILERESPONSEBODY_HPP_

#include <buffer/impl/BaseBuffer.hpp>
#include <http/response/body/IResponseBody.hpp>
#include <io/FileDescriptor.hpp>
#include <nio/NIOSelector.hpp>

class FileDescriptorBuffer;

class FileResponseBody :
		public IResponseBody,
		NIOSelector::Callback
{
	private:
		FileDescriptorBuffer &m_fdBuffer;

	private:
		FileResponseBody();
		FileResponseBody(const FileResponseBody &other);

		FileResponseBody&
		operator=(const FileResponseBody &other);

	public:
		FileResponseBody(FileDescriptorBuffer &fdBuffer);

		virtual
		~FileResponseBody();

		bool
		store(BaseBuffer &buffer);

		bool
		readable(FileDescriptor &fd);

		bool
		isDone();
};

#endif /* FILERESPONSEBODY_HPP_ */
