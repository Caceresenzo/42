/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unit.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:18:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/25 23:18:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception/Exception.hpp>
#include <tests/case/TestCase.hpp>
#include <util/ContainerBuilder.hpp>
#include <util/Enum.hpp>
#include <log/Logger.hpp>
#include <log/LoggerFactory.hpp>
#include <log/LogLevel.hpp>
#include <options/CommandLine.hpp>
#include <options/Option.hpp>
#include <options/OptionParser.hpp>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

static Logger &LOG = LoggerFactory::get("test-main");

std::map<std::string, std::list<TestCase> > g_test_units_and_cases;

const Option OPT_HELP('h', "help", "display this help message");
const Option OPT_VERSION('v', "version", "display application's version");
const Option OPT_LOG_LEVEL('l', "log-level", "change the log-level", "level");
const Option OPT_CONTINUE('c', "continue", "don't stop at an error");
const Option OPT_PRINT_LOCATION('p', "print-location", "print test's location");

int
test_main(int argc, char **argv, char **envp)
{
	const char *program = argv[0];

	const LogLevel *level = LogLevel::INFO;
	bool doContinue = false;
	bool printLocation = false;

	std::list<const Option*> lst;
	lst.push_back(&OPT_HELP);
	lst.push_back(&OPT_LOG_LEVEL);
	lst.push_back(&OPT_CONTINUE);
	lst.push_back(&OPT_PRINT_LOCATION);

	OptionParser parser(lst);

	try
	{
		CommandLine commandLine = parser.parse(argc, argv);

		if (commandLine.has(OPT_HELP))
		{
			std::vector<std::string> authors = ContainerBuilder<std::string>()
			/**/.add("Enzo CACERES <ecaceres@student.42.fr>")
			/**/.add("Alice TETU <alicetetu@student.42.fr>")
			/**/.build();

			std::cout << parser.help(program, "A small web server", authors) << std::endl;
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

		if (commandLine.has(OPT_CONTINUE))
			doContinue = true;

		if (commandLine.has(OPT_PRINT_LOCATION))
			printLocation = true;
	}
	catch (Exception &exception)
	{
		std::cerr << argv[0] << ": " << exception.what() << std::endl;
		std::cerr << "Try '" << argv[0] << " --help' for more informations." << std::endl;
		return (1);
	}

	LogLevel::ACTIVE = level;

	LOG.debug() << "Set log level to: " << level->name() << std::endl;

	LOG.info() << "Starting test units" << std::endl;

	for (std::map<std::string, std::list<TestCase> >::iterator it = g_test_units_and_cases.begin(); it != g_test_units_and_cases.end(); it++)
	{
		const std::string &unit = it->first;
		const std::list<TestCase> &cases = it->second;

		LOG.info() << std::endl;
		LOG.info() << "UNIT: " << unit << std::endl;

		int index = 0;
		for (std::list<TestCase>::const_iterator it2 = cases.begin(); it2 != cases.end(); it2++)
		{
			const TestCase &testCase = *it2;

			std::ostream &out = LOG.info() << "  CASE " << ++index << "/" << cases.size() << ": " << it2->name();

			if (printLocation)
				out << " (at " << it2->location() << ")";

			out << std::endl;

			if ((*(testCase.function()))(argc, argv, envp))
			{
				if (!doContinue)
					return (1);
			}
		}
	}

	return (0);
}
