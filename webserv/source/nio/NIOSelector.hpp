/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 23:38:08 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/07 23:38:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIOSELECTOR_HPP_
# define NIOSELECTOR_HPP_

#include <io/FileDescriptor.hpp>
#include <util/FileDescriptorSet.hpp>
#include <util/Singleton.hpp>
#include <map>

class Logger;
class Time;
class FileDescriptorBuffer;

class NIOSelector :
		public Singleton<NIOSelector>
{
	public:
		class Callback;

		enum Operation
		{
			NONE/*   */= 0b000,
			ACCEPT/* */= 0b001, /* same as READ */
			READ/*   */= 0b010,
			WRITE/*  */= 0b100,
		};

		typedef std::map<int, int> OperationConfigMap;
		typedef std::map<int, Callback*> CallbackMap;
		typedef std::map<int, FileDescriptor*> FileDescriptorMap;

	public:
		static Logger &LOG;

	private:
		FileDescriptorSet m_fds;
		FileDescriptorSet m_read;
		FileDescriptorSet m_write;
		int m_highest;
		OperationConfigMap m_operationConfig;
		CallbackMap m_callbacks;
		FileDescriptorMap m_fileDescriptors;

	public:
		NIOSelector();
		NIOSelector(const NIOSelector &other);

		virtual
		~NIOSelector();

		NIOSelector&
		operator=(const NIOSelector &other);

		void
		add(FileDescriptor &fd, Callback &callback, int operations = READ | WRITE);

		void
		update(FileDescriptor &fd, int operations = READ | WRITE);

		void
		updateWithout(FileDescriptor &fd, int operations);

		void
		remove(FileDescriptor &fd);

		int
		select(FileDescriptorSet *read, FileDescriptorSet *write, struct timeval *timeout = 0);

		int
		operations(FileDescriptor &fd) const;

		const FileDescriptorSet&
		fds() const;

		const FileDescriptorSet&
		readFds() const;

		const FileDescriptorSet&
		writeFds() const;

	private:
		void
		update(int fd, int operations);

		void
		updateWithout(int fd, int operations);

		int
		operations(int fd) const;

		void
		addToSets(int fd, int operations);

		bool
		removeFromSets(int fd);

		void
		recomputeHighestByDecreasing();

	public:
		void
		debug(const Logger &logger, FileDescriptorSet &readFds, FileDescriptorSet &writeFds, bool forced = false);

		static void
		debug(const Logger &logger, const NIOSelector &selector, FileDescriptorSet &readFds, FileDescriptorSet &writeFds, bool forced = false);

	public:
		class Callback
		{
			public:
				virtual
				~Callback();

				virtual bool
				readable(FileDescriptor &fd);

				virtual bool
				writable(FileDescriptor &fd);
		};
};

#endif /* NIOSELECTOR_HPP_ */
