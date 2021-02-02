/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RootBlock.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:13:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/26 00:13:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOTBLOCK_HPP_
# define ROOTBLOCK_HPP_

#include <config/block/CGIBlock.hpp>
#include <config/block/MIMEBlock.hpp>
#include <config/block/ServerBlock.hpp>
#include <util/Optional.hpp>
#include <list>
#include <string>

class RootBlock
{
	public:
		typedef std::list<const ServerBlock*> slist;
		typedef slist::const_iterator sciterator;

		typedef std::list<const CGIBlock*> clist;
		typedef clist::const_iterator cciterator;

	public:
		static const int DEFAULT_MAX_ACTIVE_CLIENT;
		static const int DEFAULT_TIMEOUT;
		static const DataSize DEFAULT_MAX_BODY_SIZE;

	private:
		Optional<std::string> m_root;
		Optional<const MimeBlock*> m_mimeBlock;
		Optional<slist> m_serverBlocks;
		Optional<clist> m_cgiBlocks;
		Optional<long> m_maxActiveClient;
		Optional<long> m_timeout;

	private:
		RootBlock(const RootBlock &other);

		RootBlock&
		operator =(const RootBlock &other);

	public:
		RootBlock();

		virtual
		~RootBlock();

		RootBlock&
		root(const std::string &root);

		RootBlock&
		mimeBlock(const MimeBlock &mimeBlock);

		RootBlock&
		serverBlocks(const std::list<const ServerBlock*> &serverBlocks);

		RootBlock&
		cgiBlocks(const std::list<const CGIBlock*> &cgiBlocks);

		RootBlock&
		maxActiveClient(long maxActiveClient);

		RootBlock&
		timeout(long timeout);

		inline const Optional<std::string>&
		root(void) const
		{
			return (m_root);
		}

		inline const Optional<MimeBlock const*>&
		mimeBlock(void) const
		{
			return (m_mimeBlock);
		}

		inline const Optional<std::list<const ServerBlock*> >&
		serverBlocks(void) const
		{
			return (m_serverBlocks);
		}

		inline const Optional<std::list<const CGIBlock*> >&
		cgiBlocks(void) const
		{
			return (m_cgiBlocks);
		}

		inline const Optional<long>&
		maxActiveClient(void) const
		{
			return (m_maxActiveClient);
		}

		inline const Optional<long>&
		timeout(void) const
		{
			return (m_timeout);
		}

		bool
		hasCGI(const std::string &name) const;

		const CGIBlock&
		getCGI(const std::string &name) const;
};

#endif /* ROOTBLOCK_HPP_ */
