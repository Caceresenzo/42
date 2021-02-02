/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 23:36:43 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/26 17:05:49 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <exception/IllegalStateException.hpp>
#include <io/File.hpp>
#include <io/FileDescriptor.hpp>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <util/FilenameUtils.hpp>
#include <util/StringUtils.hpp>
#include <iostream>

File::File() :
		m_path()
{
}

File::File(const std::string &path) :
		m_path(path)
{
}

File::File(const File &parent, const std::string &path) :
		m_path(concatPaths(parent.path(), path))
{
}

File::File(const File &parent, const File &child) :
		m_path(concatPaths(parent.path(), child.path()))
{
}

File::File(const std::string &parent, const std::string &path) :
		m_path(concatPaths(parent, path))
{
}

File::File(const File &other) :
		m_path(other.m_path)
{
}

File::~File()
{
}

File
File::operator =(const File &other)
{
	if (this != &other)
		m_path = other.m_path;

	return (*this);
}

bool
File::exists() const
{
	struct stat st;
	if (::stat(m_path.c_str(), &st) == -1)
	{
		int error = errno;
		errno = 0;

		if (error == ENOENT)
			return (false);

		throw ioException();
	}

	return (true);
}

bool
File::isFile() const
{
	return (S_ISREG(doStat().st_mode));
}

bool
File::isDirectory() const
{
	return (S_ISDIR(doStat().st_mode));
}

bool
File::isExecutable() const
{
	return (doStat().st_mode & S_IXUSR);
}

bool
File::createNewFile(mode_t mode) const
{
	int fd;

	std::string copy = m_path;
	std::string previousStr = "";
	std::size_t found;
	
	while ((found = copy.find('/')) != std::string::npos)
	{
		std::string newPath = copy.substr(0, found);
		std::string remainedPath = copy.substr(found + 1, std::string::npos);
		if (newPath == "./" || newPath == "/")
		{
			previousStr = newPath;
			copy = remainedPath;
		}
		else
		{
			File file(previousStr + "/" + newPath);
			if (!file.exists())
				mkdir(file.path().c_str(), 0777);
			previousStr = newPath;
			copy = remainedPath;
		}

	}
	if ((fd = ::open(m_path.c_str(), O_CREAT, mode)) == -1) //TOTO create directory if needed
	{
		errno = 0;
	
		return (false); //TODO handle errors
	}

	close(fd);

	return (true);
}

size_t
File::length() const
{
	return (doStat().st_size);
}

Time
File::lastModified() const
{
	return (Time(doStat().st_mtime));
}

std::string
File::name() const
{
	return (FilenameUtils::getName(m_path));
}

FileDescriptor*
File::open(int flags, mode_t mode) const
{
	int fd;
	if ((fd = ::open(m_path.c_str(), flags, mode)) == -1)
		throw ioException();

	try
	{
		return (FileDescriptor::wrap(fd));
	}
	catch (...)
	{
		::close(fd);

		throw;
	}
}

void
File::remove(void) const
{
	if (isDirectory())
		::rmdir(m_path.c_str());
	else if (isFile())
		::unlink(m_path.c_str());
	else
		throw IllegalStateException(m_path + ": not a directory or a file");
}

bool
File::tryRemove(void) const
{
	try
	{
		remove();

		return (true);
	}
	catch (Exception &exception)
	{
		return (false);
	}
}

File
File::absolute() const
{
	return (currentDirectory().path() + "/" + m_path);
}

File
File::parent() const
{
	if (m_path.empty())
		return (std::string("/"));

	std::string::size_type stopAt = std::string::npos;

	if (StringUtils::last(m_path) == '/')
	{
		stopAt = 0;

		for (std::string::size_type n = m_path.size(); n != 0; n--)
		{
			std::string::size_type index = n - 1;

			if (m_path[index] != '/')
			{
				stopAt = index;
				break;
			}
		}
	}

	std::string::size_type lastAt;
	if (stopAt == 0 || (lastAt = m_path.rfind('/', stopAt)) == 0)
		return (std::string("/")); /* root */

	if (lastAt == std::string::npos)
		return (m_path + "/../");

	return (m_path.substr(0, lastAt));
}

std::list<File>
File::list() const
{
	struct stat st;
	if (::stat(m_path.c_str(), &st) == -1)
		throw ioException();

	if (!S_ISDIR(st.st_mode))
		throw IOException(m_path, ENOTDIR);

	DIR *dir = ::opendir(m_path.c_str());
	if (!dir)
		throw ioException();

	std::list<File> files;

	struct dirent *entry;
	while ((entry = ::readdir(dir)))
		files.push_back(File(m_path + '/' + entry->d_name));

	::closedir(dir);

	return (files);
}

std::string
File::concatPaths(const std::string &a, const std::string &b)
{
	bool aEnd = StringUtils::last(a) == '/';
	bool bStart = StringUtils::first(b) == '/';

	if (aEnd && bStart)
		return (a + b.substr(1));

	if (aEnd ^ bStart)
		return (a + b);

	return (a + '/' + b);
}

struct stat
File::doStat() const
{
	struct stat st;
	if (::stat(m_path.c_str(), &st) == -1)
		throw ioException();

	return (st);
}

File
File::currentDirectory()
{
	char *cwd = ::getcwd(NULL, 0);

	if (!cwd)
		throw resetErrnoAndReturn(IOException("getcwd", errno));

	std::string str = cwd;
	free(cwd);

	return (File(str));
}
