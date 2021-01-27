/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIBlock.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/03 11:20:53 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIBLOCK_HPP_
# define CGIBLOCK_HPP_

#include <util/Optional.hpp>
#include <list>
#include <map>
#include <string>

class CGIBlock
{
	private:
		std::string m_name;
		Optional<std::string> m_path;
		Optional<bool> m_handleNotFound;
		Optional<std::list<std::string> > m_extensions;
		Optional<std::map<std::string, std::string> > m_environment;

	private:
		CGIBlock();
		CGIBlock(const CGIBlock &other);

		CGIBlock&
		operator=(const CGIBlock &other);

	public:
		CGIBlock(const std::string &name);

		virtual
		~CGIBlock();

		CGIBlock&
		path(const std::string &path);

		CGIBlock&
		handleNotFound(bool handleNotFound);

		CGIBlock&
		extensions(const std::list<std::string> &extensions);

		CGIBlock&
		environment(const std::map<std::string, std::string> &environment);

		inline const std::string&
		name(void) const
		{
			return (m_name);
		}

		inline const Optional<std::string>&
		path(void) const
		{
			return (m_path);
		}

		inline const Optional<bool>&
		handleNotFound(void) const
		{
			return (m_handleNotFound);
		}

		inline const Optional<std::list<std::string> >&
		extensions(void) const
		{
			return (m_extensions);
		}

		inline const Optional<std::map<std::string, std::string> >&
		environment(void) const
		{
			return (m_environment);
		}

		bool
		exists(void) const;

		bool
		hasExtension(const std::string &extension) const;
};

#endif /* CGIBLOCK_HPP_ */
