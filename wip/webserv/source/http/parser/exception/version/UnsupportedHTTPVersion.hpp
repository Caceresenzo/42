/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UnsupportedHTTPVersion.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:55:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSUPPORTEDHTTPVERSION_HPP_
# define UNSUPPORTEDHTTPVERSION_HPP_

#include <http/parser/exception/HTTPRequestException.hpp>
#include <string>

class UnsupportedHTTPVersion :
		public HTTPRequestException
{
	public:
		UnsupportedHTTPVersion();
		UnsupportedHTTPVersion(const std::string &message);
		UnsupportedHTTPVersion(const UnsupportedHTTPVersion &other);

		virtual
		~UnsupportedHTTPVersion() throw ();

		UnsupportedHTTPVersion&
		operator=(const UnsupportedHTTPVersion &other);

	public:
		static UnsupportedHTTPVersion
		of(int major, int minor);
};

#endif /* UNSUPPORTEDHTTPVERSION_HPP_ */
