/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:10:59 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/12 16:59:33 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONBLOCK_HPP_
# define LOCATIONBLOCK_HPP_

#include <config/block/AuthBlock.hpp>
#include <util/Optional.hpp>
#include <list>
#include <string>
#include <unit/DataSize.hpp>

class LocationBlock
{
	private:
		std::string m_path;
		Optional<std::list<std::string> > m_methods;
		Optional<std::string> m_root;
		Optional<bool> m_listing;
		Optional<std::list<std::string> > m_index;
		Optional<std::string> m_cgi;
		Optional<AuthBlock const*> m_auth;
		Optional<DataSize> m_maxBodySize;

	private:
		LocationBlock(void);
		LocationBlock(const LocationBlock &other);

		LocationBlock&
		operator=(const LocationBlock &other);

	public:
		LocationBlock(const std::string &path);

		virtual
		~LocationBlock();

		LocationBlock&
		methods(const std::list<std::string> &methods);

		LocationBlock&
		root(const std::string &root);

		LocationBlock&
		listing(bool listing);

		LocationBlock&
		index(const std::list<std::string> &files);

		LocationBlock&
		cgi(const std::string &cgi);

		LocationBlock&
		auth(const AuthBlock &auth);

		LocationBlock&
		maxBodySize(const DataSize &maxBodySize);

		inline const std::string&
		path(void) const
		{
			return (m_path);
		}

		inline const Optional<std::list<std::string> >&
		methods(void) const
		{
			return (m_methods);
		}

		inline const Optional<std::string>&
		root(void) const
		{
			return (m_root);
		}

		inline const Optional<bool>&
		listing(void) const
		{
			return (m_listing);
		}

		inline const Optional<std::list<std::string> >&
		index(void) const
		{
			return (m_index);
		}

		inline const Optional<std::string>&
		cgi(void) const
		{
			return (m_cgi);
		}

		inline const Optional<AuthBlock const*>&
		auth(void) const
		{
			return (m_auth);
		}

		inline const Optional<DataSize>&
		maxBodySize(void) const
		{
			return (m_maxBodySize);
		}

		bool
		hasMethod(const std::string &name) const;
};

#endif /* LOCATIONBLOCK_HPP_ */
