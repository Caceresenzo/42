/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPFindLocation.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:24:48 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/17 10:02:05 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPFINDLOCATION_HPP_
# define HTTPFINDLOCATION_HPP_

#include <config/block/ServerBlock.hpp>
#include <util/Optional.hpp>


class HTTPFindLocation
{	
	private:
		std::string m_clientPath;
		std::list<const LocationBlock*> m_serverLocations;
		Optional<const LocationBlock*> m_locationBlock;
		
	public:
		HTTPFindLocation();
		HTTPFindLocation(std::string clientPath, std::list<const LocationBlock*> serverBlock);
		HTTPFindLocation(const HTTPFindLocation &other);
		
		virtual
		~HTTPFindLocation();

		HTTPFindLocation&
		operator =(const HTTPFindLocation &other);

		HTTPFindLocation&
		location(const LocationBlock* locationBlock);
		
		const Optional<const LocationBlock*>
		location(void) const;

		HTTPFindLocation&
		parse(void);
};

#endif /* HTTPFindLocation_HPP_ */