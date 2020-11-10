/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:34:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/block/LocationBlock.hpp>
#include <config/block/ServerBlock.hpp>
#include <config/Configuration.hpp>
#include <exception/IOException.hpp>
#include <http/HTTPMethod.hpp>
#include <http/HTTPOrchestrator.hpp>
#include <sys/errno.h>
#include <util/ContainerBuilder.hpp>
#include <util/unit/DataSize.hpp>
#include <string>
#include <vector>

int
main(int argc, char **argv)
{
	HTTPMethod::loadDefaults();

	Configuration configuration(ContainerBuilder<ServerBlock>() //
	/**/.add(ServerBlock()
	/**//**/.port(1502)
	/**//**/.host("127.0.0.1")
	/**//**/.name("boxplay.io")
	/**//**/.maxBodySize(DataSize::ofMegabytes(10))
	/**//**/.root("/var/www/html")
	/**//**/.locations(ContainerBuilder<LocationBlock>()
	/**//**//**/.add(LocationBlock()
	/**//**//**//**/.allowedMethods(ContainerBuilder<std::string>()
	/**//**//**//**//**/.add("GET")
	/**//**//**//**//**/.add("HEAD")
	/**//**//**//**//**/.add("POST")
	/**//**//**//**//**/.build())
	/**//**//**//**/.indexFiles(ContainerBuilder<std::string>()
	/**//**//**//**//**/.add("index.html")
	/**//**//**//**//**/.add("index-default.html")
	/**//**//**//**//**/.build())
	/**//**//**//**/.listing(true))
	/**//**//**/.build()))
	/**/.add(ServerBlock()
	/**//**/.port(2051)
	/**//**/.host("127.0.0.1")
	/**//**/.name("boxplay2.io")
	/**//**/.maxBodySize(DataSize::ofMegabytes(10))
	/**//**/.root("/var/www/html"))
	/**/.build());

	HTTPOrchestrator::create(configuration).start();

	throw IOException("ORCHESTRATOR LOOP HAS BEEN EXITED", errno);

	return (0);
}
