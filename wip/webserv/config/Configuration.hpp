/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:33:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:33:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP_
# define CONFIGURATION_HPP_

#include <config/block/ServerBlock.hpp>
#include <vector>

class Configuration
{
	public:
		typedef std::vector<ServerBlock>::const_iterator siterator;

	private:
		std::vector<ServerBlock> m_servers;

	public:
		Configuration(void);
		Configuration(std::vector<ServerBlock> servers);
		Configuration(const Configuration &other);

		virtual
		~Configuration();

		Configuration&
		operator=(const Configuration &other);

		const std::vector<ServerBlock>&
		servers(void) const;
};

#endif /* CONFIGURATION_HPP_ */
