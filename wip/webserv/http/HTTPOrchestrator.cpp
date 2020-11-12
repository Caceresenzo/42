/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPOrchestrator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:34:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 14:34:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/ServerBlock.hpp>
#include <sys/stat.h>
#include <dirent.h>
#include <exception/IOException.hpp>
#include <http/HttpRequestParser.hpp>
#include <http/HttpResponse.hpp>
#include <http/HTTPHeaderFields.hpp>
#include <http/HTTPOrchestrator.hpp>
#include <http/HTTPStatus.hpp>
#include <http/HTTPVersion.hpp>
#include <http/mime/MimeRegistry.hpp>
#include <io/SocketServer.hpp>
#include <sys/select.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>

#ifdef __linux__
# include <unistd.h>
#elif __APPLE__
# include <unistd.h>
#elif __CYGWIN__
# include <sys/unistd.h>
#else
# error Unknown plateform
#endif

#include <util/Optional.hpp>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class HttpResponse;

typedef enum
{
	CS_CONNECTED = 1,
	CS_HEADER,
	CS_BODY,
	CS_ERROR
} client_status;

typedef struct
{
		client_status status;
		std::string line;
		HttpRequestParser parser;
		bool header_read;
		unsigned long last_action;
		HTTPServer *httpServer;
		HttpResponse *response;
} client;

unsigned long
seconds()
{
	struct timeval val;
	if (gettimeofday(&val, NULL))
		return (0);

	return (val.tv_sec);
}

HTTPOrchestrator::HTTPOrchestrator(const Configuration &configuration, const std::vector<HTTPServer> &servers) :
		m_configuration(configuration),
		m_servers(servers)
{
}

HTTPOrchestrator::~HTTPOrchestrator()
{
}

void
HTTPOrchestrator::prepare(void)
{
	iterator it = m_servers.begin();
	iterator ite = m_servers.end();

	while (it != ite)
	{
		try
		{
			it->prepare();
		}
		catch (...)
		{
			unprepare();

			throw;
		}

		it++;
	}
}

void
HTTPOrchestrator::unprepare(void)
{
	iterator it = m_servers.begin();
	iterator ite = m_servers.end();

	while (it != ite)
	{
		it->unprepare();

		it++;
	}
}

void
HTTPOrchestrator::start()
{
	prepare();

	MimeRegistry mimeRegistry;
	mimeRegistry.loadFromFile("mime.json");

	fd_set fds;

	FD_ZERO(&fds);

	int highest = 0;
	iterator it = m_servers.begin();
	while (it != m_servers.end())
	{
		int fd = it->serverSocket().fd();
		std::cout << "server: " << fd << std::endl;

		FD_SET(fd, &fds);

		if (fd > highest)
			highest = fd;

		it++;
	}

	fd_set read_fds;
	fd_set write_fds;

	std::cout << highest << std::endl;

	int startAt = highest + 1;

	std::map<int, client*> clients;

	while (1)
	{
		read_fds = fds;
		write_fds = fds;

		if (::select(highest + 1, &read_fds, &write_fds, NULL, NULL) == -1)
			throw IOException("select", errno);

		it = m_servers.begin();
		while (it != m_servers.end())
		{
			int server_fd = it->serverSocket().fd();

			if (FD_ISSET(server_fd, &read_fds))
			{
				try
				{
					int socket_fd = ::accept(server_fd, NULL, NULL);

					std::cout << "connected(" << socket_fd << ")" << std::endl;

					if (::fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1)
						throw IOException("fcntl", errno);

					if (socket_fd > highest)
						highest = socket_fd;

					FD_SET(socket_fd, &fds);

					client *c = new client();
//					c->status = CS_CONNECTED;
					c->last_action = seconds();
					c->header_read = false;

					clients[socket_fd] = c;
				}
				catch (Exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}

			it++;
		}

		unsigned long now = seconds();

		for (int fd = startAt; fd <= highest; fd++)
		{
			if (!FD_ISSET(fd, &fds))
				continue;

			std::map<int, client*>::iterator it = clients.find(fd);

			if (it == clients.end())
			{
				std::cout << "orphane: " << fd << std::endl;
				::close(fd);
				FD_CLR(fd, &fds);
				clients.erase(it);
				continue;
			}

			bool canRead = FD_ISSET(fd, &read_fds);
			bool canWrite = FD_ISSET(fd, &write_fds);

			client *cli = it->second;

			if (cli->last_action + 5 < now)
			{
				std::cout << "timeout: " << fd << std::endl;
				::close(fd);
				FD_CLR(fd, &fds);
				delete cli;
				clients.erase(it);

				if (fd == highest)
					highest--;

				continue;
			}

			if (canRead && !cli->header_read)
			{
				char c;
				if (::recv(fd, &c, 1, 0) > 0)
				{
//					if (c == '\n')
//						std::cout << "\\n\n";
//					else if (c == '\r')
//						std::cout << "\\r";
//					else
//						std::cout << c;
//					std::cout << std::flush;

					if (c)
					{
						cli->parser.consume(c);
						if (cli->parser.state() == HttpRequestParser::S_END && !cli->response)
						{
							std::string file = cli->parser.path().substr(1);

							int ffd = ::open(("." + cli->parser.path()).c_str(), O_RDONLY);

							HTTPHeaderFields header;
							header.date();
							header.set("Server", "webserv");

							struct stat st;
							if (ffd == -1 || ::stat(("." + cli->parser.path()).c_str(), &st) == -1)
							{
								header.contentType("text/html");
								header.contentLength(8);
								std::cout << "GET " + cli->parser.path() + " -> 404" << std::endl;
								close(ffd);

								cli->response = new HttpResponse(HTTPVersion::HTTP_1_1, *HTTPStatus::OK, header, new HttpResponse::StringBody("not found"));
							}
							else
							{
								std::cout << "GET " + cli->parser.path() + " -> 200" << std::endl;

								if (S_ISDIR(st.st_mode))
								{
									std::cout << file << std::endl;

									std::string directory = cli->parser.path() == "/" ? "." : file;

									DIR *dir = ::opendir(directory.c_str());
									std::cout << dir << std::endl;

									std::string listing = "";

									struct dirent *entry;
									while ((entry = ::readdir(dir)))
									{
										std::string lfile(entry->d_name);
										std::string absolute = directory + "/" + lfile;

										if (::stat(absolute.c_str(), &st) != -1 && S_ISDIR(st.st_mode))
										{
											lfile += '/';
										}

										listing += std::string("<a href=\"./") + lfile + "\">" + lfile + "</a><br>";
									}

									::closedir(dir);

									header.contentType("text/html");
									header.contentLength(listing.size());

									cli->response = new HttpResponse(HTTPVersion::HTTP_1_1, *HTTPStatus::OK, header, new HttpResponse::StringBody(listing));
								}
								else if (S_ISREG(st.st_mode))
								{
									header.contentType(mimeRegistry, file.substr(file.rfind(".") + 1));
									header.contentLength(st.st_size);

									cli->response = new HttpResponse(HTTPVersion::HTTP_1_1, *HTTPStatus::OK, header, new HttpResponse::FileBody(ffd));
								}
							}
						}
					}
				}
//				std::cout << "can read(" << fd << ")" << std::endl;
			}

			if (canWrite)
			{
				if (cli->response)
				{
					if (cli->response->write(fd) >= 0) // TODO Add windows support
					{
						cli->last_action = seconds();
					}
					else
					{
						std::cout << "closing: " << ::strerror(errno) << std::endl;
						::close(fd);
						FD_CLR(fd, &fds);
						delete cli->response;
						delete cli;
						clients.erase(it);

						if (fd == highest)
							highest--;
					}
				}
//				send(fd, "Hello\n", 6, 0);
//				std::cout << "can write(" << fd << ")" << std::endl;
			}
		}
	}

	it = m_servers.begin();
	while (it != m_servers.end())
	{
		int fd = it->serverSocket().fd();
		::close(fd);

		it++;
	}
}

HTTPOrchestrator
HTTPOrchestrator::create(const Configuration &configuration)
{
	typedef std::map<int, std::vector<ServerBlock> >::iterator plsiterator;

	std::map<int, std::vector<ServerBlock> > portToServersMap;

	Configuration::siterator it = configuration.servers().begin();
	Configuration::siterator ite = configuration.servers().end();

	while (it != ite)
	{
		portToServersMap[it->port().get()].push_back(*it);
		it++;
	}

	std::vector<HTTPServer> httpServers;
	plsiterator itr = portToServersMap.begin();
	plsiterator itre = portToServersMap.end();

	while (itr != itre)
	{
		httpServers.push_back(HTTPServer(itr->first, itr->second));
		itr++;
	}

	return (HTTPOrchestrator(configuration, httpServers));
}
