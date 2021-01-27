/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_util_string.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:54:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/26 00:54:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests/test_unit.hpp>
#include <util/FilenameUtils.hpp>
#include <iostream>
#include <string>

CASE("filename-util", "getName")
{
	ASSERT(FilenameUtils::getName("a/b/c.txt") == "c.txt");
	ASSERT(FilenameUtils::getName("a.txt") == "a.txt");
	ASSERT(FilenameUtils::getName("a/b/c") == "c");
	ASSERT(FilenameUtils::getName("a/b/c/") == "");

	return (0);
}

CASE("filename-util", "getExtension")
{
	ASSERT(FilenameUtils::getExtension("foo.txt") == "txt");
	ASSERT(FilenameUtils::getExtension("a/b/c.jpg") == "jpg");
	ASSERT(FilenameUtils::getExtension("a/b.txt/c") == "");
	ASSERT(FilenameUtils::getExtension("a/b/c") == "");

	return (0);
}
