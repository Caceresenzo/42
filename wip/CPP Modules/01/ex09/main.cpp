/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Logger.hpp"

int
main(void)
{
	Logger logger("log.txt");

	logger.log(DEST_CONSOLE, "Hello World From The Console");
	logger.log(DEST_FILE, "Hello World From The File");

	logger.log("garbage", "Hello World From The Garbage");
}
