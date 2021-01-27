/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileDescriptorSet.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:51:36 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 23:51:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEDESCRIPTORSET_HPP_
# define FILEDESCRIPTORSET_HPP_

#include <sys/select.h>

class FileDescriptorSet
{
	private:
		fd_set m_storage;
		int m_size;

	public:
		static const int MAX;

	public:
		FileDescriptorSet();
		FileDescriptorSet(const FileDescriptorSet &other);

		virtual
		~FileDescriptorSet();

		FileDescriptorSet&
		operator=(const FileDescriptorSet &other);

		void
		zero();

		void
		set(int n);

		void
		clear(int n);

		bool
		test(int n) const;

		int
		size() const;

		bool
		empty() const;

		fd_set&
		storage();
};

#endif /* FILEDESCRIPTORSET_HPP_ */
