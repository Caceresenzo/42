/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeRegistry.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:39:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/02 18:00:27 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIMEREGISTRY_HPP_
# define MIMEREGISTRY_HPP_

#include <http/mime/MIME.hpp>
#include <json/JsonObject.hpp>
#include <stddef.h>
#include <map>
#include <string>

class Logger;

/**
 * MIME Registry to allow an easy mapping and reverse mapping between MIME string type notation (e.g. text/csv) and a corresponding file extension.
 * This class will especially be useful when returning a file as a response to a request.
 */
class MIMERegistry
{
	private:
		typedef std::map<std::string, MIME*> map;
		typedef map::const_iterator const_iterator;

	public:
		static Logger &LOG;

	private:
		map m_mapping; /* mime type -> mime */
		map m_reverse_mapping; /* file extension -> mime */

	public:
		MIMERegistry(void);
		MIMERegistry(const map &mapping, const map &reverse_mapping);
		MIMERegistry(const MIMERegistry &other);

		~MIMERegistry(void);

		MIMERegistry&
		operator =(const MIMERegistry &other);

	private:
		/**
		 * Copy a mapping from an instance to another.
		 * This will do a deep mapping by deep copying all of the instance.
		 *
		 * @param from Source map to copy from.
		 * @param to Target map to copy to.
		 */
		void
		copyMapping(const map &from, map &to);

		/**
		 * Clear a mapping.
		 * This will call the delete operator on all of the entries.
		 *
		 * @param mapping Mapping to clear.
		 */
		void
		clearMapping(map &mapping);

	public:
		/**
		 * Add a MIME to this registry.
		 * This will add it to both normal mapping and reverse mapping.
		 *
		 * @param mime MIME to add.
		 */
		void
		add(const MIME &mime);

		/**
		 * Clear all currently loaded MIME.
		 */
		void
		clear(void);

		/**
		 * Find a MIME by a MIME type. (normal mapping)
		 *
		 * @param type MIME type. (e.g. text/csv)
		 * @return Found MIME instance. (or null if none)
		 */
		const MIME*
		findByMimeType(const std::string &type) const;

		/**
		 * Find a MIME by a file extension. (reverse mapping)
		 *
		 * @param type File extension. (without the dot `.`)
		 * @return Found MIME instance. (or null if none)
		 */
		const MIME*
		findByFileExtension(const std::string &extension) const;

		/**
		 * Load MIMEs from a compatible file.
		 *
		 * @param path File path.
		 */
		void
		loadFromFile(const std::string &path);

		void
		loadFromJson(const std::string &path, const JsonObject &jsonObject);

		/**
		 * Get the normal mapping map size.
		 *
		 * @return Normal mapping's map size.
		 */
		size_t
		size() const;
};

#endif /* MIMEREGISTRY_HPP_ */
