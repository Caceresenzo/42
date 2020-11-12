/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Option.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:29:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 16:33:55 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_HPP_
# define OPTION_HPP_

#include <iostream>

class Option
{
	private:
		char m_short;
		std::string m_long;
		std::string m_description;
		bool m_hasValue;
		std::string m_valueName;
		std::string m_value;

	public:
		Option();
		Option(const Option &other);

		virtual
		~Option();

		Option&
		operator=(const Option &other);
};

// ./webserv --check --config-file ./x.json


/**
 * webserv v01
 * 
 * -h	--help			: no value : display this help message
 * -c	--check			: no value : only check the config file
 * -f	--config file	: <file>   : specify the config file
 * 
 * 
 * */

/**
 *
 * main:
 * 
 * - = short
 * -- = long
 * 
 * if (str startWith -)
 * 
 * Option helpOption('h', "help", "display this help message");
 * Option checkOption('c', "check", "only check the config file");
 * Option configFileOption('f', "config-file", "specify the config file", "file");
 * 
 * // c (...)
 * // c (..., valueName)
 * 
 * OptionParser parser(std::list(&checkOption, &configFileOption, ...))
 * 
 * try {
 * 		parser.parse(argc, argv);
 * } catch (...) {
 * 		std::cerr << failed to parse;
 * 		::exit(1);
 * }
 * 
 * std::string configFile = "./conf.json";
 * 
 * if(parser.has(configFileOption)) {
 * 		configFile = configFileOption.value();
 * }
 * 
 * if (file does not exists (configFile)) {
 * 		std::cerr << config file not found,
 * 		exit(1);
 * }
 * 
 * if (parser.isPresent(checkOption)) {
 * 		// CHECK CONFIG FILE
 * 		::exit(0);
 * }
 * 
 * // Bind JSON to CPP
 * // Start orchestrator
 * 
 */

#endif /* OPTION_HPP_ */
