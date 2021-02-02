/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilenameUtils.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:15:11 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/21 15:15:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILENAMEUTILS_HPP_
# define FILENAMEUTILS_HPP_

#include <string>
#include <os/detect_platform.h>

# if IS_UNIX
#  define PLATFORM_SEPARATOR '/'
# elif IS_WINDOWS
#  define PLATFORM_SEPARATOR '\\'
# else
#  error "Unknown platform file separator"
# endif

# define EXTENSION_SEPARATOR '.'

class FilenameUtils
{
	private:
		static std::string::size_type NOT_FOUND;

	private:
		FilenameUtils();
		FilenameUtils(const FilenameUtils &other);

		virtual
		~FilenameUtils();

		FilenameUtils&
		operator=(const FilenameUtils &other);

	public:
		static std::string
		getName(const std::string &fileName);

		static std::string
		getExtension(const std::string &fileName);

		static std::string::size_type
		indexOfLastSeparator(const std::string &fileName);

		static std::string::size_type
		indexOfExtension(const std::string &fileName);
};

#endif /* FILENAMEUTILS_HPP_ */
