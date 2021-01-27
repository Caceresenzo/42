/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_nio_selector.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:09:01 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/08 02:09:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <buffer/impl/BaseBuffer.hpp>
#include <io/FileDescriptor.hpp>
#include <nio/NIOSelector.hpp>
#include <tests/test_unit.hpp>
#include <string>

CASE("nio-selector", "add")
{
	FileDescriptor fd0(0);
	FileDescriptor fd1(1);
	FileDescriptor fd2(2);
	FileDescriptor fd3(3);
	NIOSelector nioSelector;

	NIOSelector::Callback callback;

	nioSelector.add(fd0, callback, NIOSelector::READ);
	ASSERT(nioSelector.readFds().test(0));
	ASSERT(!nioSelector.writeFds().test(0));

	nioSelector.add(fd1, callback, NIOSelector::WRITE);
	ASSERT(!nioSelector.readFds().test(1));
	ASSERT(nioSelector.writeFds().test(1));

	nioSelector.add(fd2, callback, NIOSelector::READ | NIOSelector::WRITE);
	ASSERT(nioSelector.readFds().test(2));
	ASSERT(nioSelector.writeFds().test(2));

	nioSelector.add(fd3, callback, NIOSelector::NONE);
	ASSERT(!nioSelector.readFds().test(3));
	ASSERT(!nioSelector.writeFds().test(3));

	return (0);
}

CASE("nio-selector", "update")
{
	FileDescriptor fd0(0);
	NIOSelector nioSelector;

	NIOSelector::Callback callback;

	nioSelector.add(fd0, callback, NIOSelector::NONE);

	nioSelector.update(fd0, NIOSelector::READ);
	ASSERT(nioSelector.readFds().test(0));
	ASSERT(!nioSelector.writeFds().test(0));
	ASSERT(nioSelector.fds().test(0));

	nioSelector.update(fd0, NIOSelector::WRITE);
	ASSERT(!nioSelector.readFds().test(0));
	ASSERT(nioSelector.writeFds().test(0));
	ASSERT(nioSelector.fds().test(0));

	nioSelector.update(fd0, NIOSelector::READ | NIOSelector::WRITE);
	ASSERT(nioSelector.readFds().test(0));
	ASSERT(nioSelector.writeFds().test(0));
	ASSERT(nioSelector.fds().test(0));

	return (0);
}

CASE("nio-selector", "updateWithout")
{
	FileDescriptor fd0(0);
	NIOSelector nioSelector;

	NIOSelector::Callback callback;

	nioSelector.add(fd0, callback);

	nioSelector.updateWithout(fd0, NIOSelector::READ);
	ASSERT(!nioSelector.readFds().test(0));
	ASSERT(nioSelector.writeFds().test(0));
	ASSERT(nioSelector.fds().test(0));

	nioSelector.updateWithout(fd0, NIOSelector::WRITE);
	ASSERT(!nioSelector.readFds().test(0));
	ASSERT(!nioSelector.writeFds().test(0));
	ASSERT(nioSelector.fds().test(0));

	return (0);
}

CASE("nio-selector", "remove")
{
	FileDescriptor fd0(0);
	FileDescriptor fd1(1);
	NIOSelector nioSelector;

	NIOSelector::Callback callback;

	nioSelector.add(fd0, callback);
	nioSelector.add(fd1, callback);

	nioSelector.remove(fd0);
	ASSERT(!nioSelector.readFds().test(0));
	ASSERT(!nioSelector.writeFds().test(0));
	ASSERT(!nioSelector.fds().test(0));

	nioSelector.remove(fd1);
	ASSERT(!nioSelector.readFds().test(1));
	ASSERT(!nioSelector.writeFds().test(1));
	ASSERT(!nioSelector.fds().test(1));

	return (0);
}
