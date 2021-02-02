/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilenameUtils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:15:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/21 15:15:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/FilenameUtils.hpp>

std::string::size_type FilenameUtils::NOT_FOUND = std::string::size_type(-1);

std::string
FilenameUtils::getName(const std::string &fileName)
{
	return (fileName.substr(indexOfLastSeparator(fileName) + 1));
}

std::string
FilenameUtils::getExtension(const std::string &fileName)
{
	std::string::size_type index = indexOfExtension(fileName);

	if (index == NOT_FOUND)
		return ("");

	return (fileName.substr(index + 1));
}

std::string::size_type
FilenameUtils::indexOfLastSeparator(const std::string &fileName)
{
	return (fileName.rfind(PLATFORM_SEPARATOR));
}

std::string::size_type
FilenameUtils::indexOfExtension(const std::string &fileName)
{
	long extensionPos = (long)fileName.rfind(EXTENSION_SEPARATOR);
	long lastSeparator = (long)indexOfLastSeparator(fileName);

	return (lastSeparator > extensionPos ? NOT_FOUND : extensionPos);
}
