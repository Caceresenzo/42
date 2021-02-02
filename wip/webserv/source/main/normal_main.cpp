/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_main.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:29:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 01:29:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <config/Configuration.hpp>
#include <config/exceptions/ConfigurationBindException.hpp>
#include <config/exceptions/ConfigurationValidateException.hpp>
#include <signal.h>
#include <exception/IOException.hpp>
#include <http/HTTPOrchestrator.hpp>
#include <json/JsonException.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <log/LogLevel.hpp>
#include <options/CommandLine.hpp>
#include <options/Option.hpp>
#include <options/OptionParser.hpp>
#include <util/ContainerBuilder.hpp>
#include <util/Enum.hpp>
#include <util/Environment.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <webserv.hpp>
#include <csignal>
#include <iostream>
#include <list>
#include <string>
#include <vector>

const Option OPT_HELP('h', "help", "display this help message");
const Option OPT_VERSION('v', "version", "display application's version");
const Option OPT_LOG_LEVEL('l', "log-level", "change the log-level", "level");
const Option OPT_CHECK('c', "check", "only check the config file");
const Option OPT_CONFIG_FILE('f', "config-file", "specify the config file", "file");
const Option OPT_IGNORE_MIME_INCLUDES_ERROR('m', "ignore-mime-includes-error", "only warn when a MIME file inclusion cause an error");
const Option OPT_IGNORE_GRACEFUL_STOP('s', "ignore-graceful-stop", "avoid doing a graceful stop when receiving a INT signal");
const Option OPT_NO_COLOR('n', "no-color", "don't use color in the console");

static Logger &LOG = LoggerFactory::get("main");
static HTTPOrchestrator *httpOrchestrator = NULL;

static bool gracefulShutdown = false;

void
sighandler_term(int sig)
{
	if (httpOrchestrator)
	{
		gracefulShutdown = true;
		::signal(sig, SIG_DFL);
		LOG.info() << "Graceful shutdown asked... (do CTRL-C again to quit immediately)" << std::endl;
		httpOrchestrator->stop();
	}
}

int
normal_main(int argc, char **argv, char **envp)
{
	const char *program = argv[0];

	const LogLevel *level = LogLevel::INFO;
	bool checkOnly = false;
	bool ignoreMimeIncludesError = false;
	bool ignoreGracefulStop = false;
	bool noColor = false;
	std::string configFile = "conf.json";

	std::list<const Option*> lst;
	lst.push_back(&OPT_HELP);
	lst.push_back(&OPT_VERSION);
	lst.push_back(&OPT_LOG_LEVEL);
	lst.push_back(&OPT_CHECK);
	lst.push_back(&OPT_CONFIG_FILE);
	lst.push_back(&OPT_IGNORE_MIME_INCLUDES_ERROR);
	lst.push_back(&OPT_IGNORE_GRACEFUL_STOP);
	lst.push_back(&OPT_NO_COLOR);

	OptionParser parser(lst);

	try
	{
		CommandLine commandLine = parser.parse(argc, argv);

		if (commandLine.has(OPT_HELP))
		{
			std::vector<std::string> authors = ContainerBuilder<std::string>()
			/**/.add("Enzo CACERES <ecaceres@student.42.fr>")
			/**/.add("Alice TETU <alicetetu@student.42.fr>")
			/**/.add("Romain SANCHEZ <rosanche@student.42.fr>")
			/**/.build();

			std::cout << parser.help(program, "A small web server", authors) << std::endl;
			return (0);
		}

		if (commandLine.has(OPT_VERSION))
		{
			std::cout << APPLICATION_NAME_AND_VERSION << std::endl;
			return (0);
		}

		if (commandLine.has(OPT_LOG_LEVEL))
		{
			const std::string &input = commandLine.last(OPT_LOG_LEVEL);

			const LogLevel *foundLevel = LogLevel::find(input);
			if (foundLevel)
				level = foundLevel;
			else
				throw Exception("unknown log level: " + input);
		}

		if (commandLine.has(OPT_CHECK))
			checkOnly = true;

		if (commandLine.has(OPT_CONFIG_FILE))
			configFile = commandLine.last(OPT_CONFIG_FILE);

		if (commandLine.has(OPT_IGNORE_MIME_INCLUDES_ERROR))
			ignoreMimeIncludesError = true;

		if (commandLine.has(OPT_IGNORE_GRACEFUL_STOP))
			ignoreGracefulStop = true;

		if (commandLine.has(OPT_NO_COLOR))
			noColor = true;
	}
	catch (Exception &exception)
	{
		std::cerr << argv[0] << ": " << exception.what() << std::endl;
		std::cerr << "Try '" << argv[0] << " --help' for more informations." << std::endl;
		return (1);
	}

	LogLevel::ACTIVE = level;
	LogLevel::COLORED = !noColor;

	LOG.debug() << "Set log level to: " << level->name() << std::endl;

	Environment::set(envp);

	if (checkOnly)
	{
		try
		{
			delete Configuration::fromJsonFile(configFile, ignoreMimeIncludesError);
		}
		catch (Exception &exception)
		{
			std::cout << "error: " << exception.message() << std::endl;
			return (1);
		}
	}
	else
	{
		try
		{
			LOG.debug() << "Loading configuration... (path: " << configFile << ")" << std::endl;

			Configuration::setInstance(Configuration::fromJsonFile(configFile, ignoreMimeIncludesError));
		}
		catch (IOException &exception)
		{
			LOG.fatal() << "Failed to read file: " << exception.message() << std::endl;
			return (1);
		}
		catch (JsonException &exception)
		{
			LOG.fatal() << "Failed to parse JSON: " << exception.message() << std::endl;
			return (1);
		}
		catch (ConfigurationBindException &exception)
		{
			LOG.fatal() << "Failed bind configuration: " << exception.message() << std::endl;
			return (1);
		}
		catch (ConfigurationValidateException &exception)
		{
			LOG.fatal() << "Failed validate configuration: " << exception.message() << std::endl;
			return (1);
		}
		catch (Exception &exception)
		{
			LOG.fatal() << "Failed create configuration: " << exception.message() << std::endl;
			return (1);
		}
	}

	if (!checkOnly)
	{
		if (!ignoreGracefulStop)
		{
			::signal(SIGINT, &sighandler_term);
			LOG.debug() << "Installed signal handler: " << (void*)&sighandler_term << std::endl;
		}

		try
		{
			httpOrchestrator = HTTPOrchestrator::create();
			httpOrchestrator->start();

			if (gracefulShutdown)
				LOG.info() << "Shutdown successfully!" << std::endl;
		}
		catch (Exception &exception)
		{
			DeleteHelper::pointer<HTTPOrchestrator>(httpOrchestrator);

			LOG.fatal() << "Failed to orchestre: " << exception.message() << std::endl;
			return (1);
		}
	}
	else
		std::cout << "well formatted and validated!" << std::endl;

	DeleteHelper::pointer<HTTPOrchestrator>(httpOrchestrator);

	return (0);
}
