/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:34:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERBLOCK_HPP_
# define SERVERBLOCK_HPP_

#include <config/block/LocationBlock.hpp>
#include <util/Optional.hpp>
#include <util/unit/DataSize.hpp>
#include <iostream>
#include <vector>

class ServerBlock
{
	public:
		Optional<int> m_port;
		Optional<std::string> m_host;
		Optional<std::string> m_name;
		Optional<DataSize> m_maxBodySize;
		Optional<std::string> m_root;
		Optional<std::vector<LocationBlock> > m_locations;

	public:
		ServerBlock();
		ServerBlock(const ServerBlock &other);

		virtual
		~ServerBlock();

		ServerBlock&
		operator=(const ServerBlock &other);

		ServerBlock&
		port(int port);

		const Optional<int>
		port(void) const;

		ServerBlock&
		host(std::string host);

		ServerBlock&
		name(std::string name);

		ServerBlock&
		maxBodySize(DataSize maxBodySize);

		ServerBlock&
		root(std::string root);

		ServerBlock&
		locations(std::vector<LocationBlock> locations);

	public:
		static const std::string DEFAULT_HOST;
};

#endif /* SERVERBLOCK_HPP_ */
