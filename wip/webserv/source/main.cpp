/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:34:02 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/09 11:26:14 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/Configuration.hpp>
#include <signal.h>
#include <log/LoggerFactory.hpp>
#include <main/normal_main.hpp>
#include <stddef.h>
#include <tests/test_unit.hpp>
#include <csignal>
#include <iostream>
#include <typeinfo>

int
main(int argc, char **argv, char **envp)
{
	int exitCode = 0;

	try
	{
		signal(SIGPIPE, SIG_IGN);

#if RUN_TESTS
		exitCode = test_main(argc, argv, envp);
#else
		exitCode = normal_main(argc, argv, envp);
#endif
	}
	catch (std::exception &exception)
	{
		exitCode = 1;

		std::cerr << "unhandled " << typeid(exception).name() << ": " << exception.what() << std::endl;
	}
	catch (...)
	{
		exitCode = 1;

		std::cerr << "unhandled catch" << std::endl;
	}

	Configuration::setInstance(NULL);
	LoggerFactory::destroy();

	return (exitCode);
}
