/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeRegistry.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:39:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/26 17:39:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIMEREGISTRY_HPP_
# define MIMEREGISTRY_HPP_

#include <http/mime/Mime.hpp>
#include <iostream>
#include <map>

class MimeRegistry
{
	private:
		typedef std::map<std::string, Mime*> map;
		typedef map::const_iterator const_iterator;

	private:
		map m_mapping; /* mime type -> mime */
		map m_reverse_mapping; /* file extension -> mime */

	public:
		MimeRegistry(void);
		MimeRegistry(const map &mapping, const map &reverse_mapping);
		MimeRegistry(const MimeRegistry &other);

		MimeRegistry&
		operator =(const MimeRegistry &other);

		void
		add(const Mime &mime);

		const Mime*
		findByMimeType(const std::string &type) const;

		const Mime*
		findByFileExtension(const std::string &type) const;

		void
		loadFromFile(const std::string &path);
};

#endif /* MIMEREGISTRY_HPP_ */
