/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChunkEncoder.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:47:44 by alicetetu         #+#    #+#             */
/*   Updated: 2020/12/21 15:47:41 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHUNKENCODER_HPP_
# define CHUNKENCODER_HPP_

#include <http/body/encoding/IHTTPBodyEncoder.hpp>
#include <util/Singleton.hpp>
#include <string>

class ChunkEncoder :
		public IHTTPBodyEncoder,
		public Singleton<ChunkEncoder>
{
	public:
		static const std::string ZERO;

	private:
		ChunkEncoder(const ChunkEncoder &other);

		ChunkEncoder&
		operator=(const ChunkEncoder &other);

	public:
		ChunkEncoder();

		virtual
		~ChunkEncoder();

		std::string
		encode(const std::string &input);

	public:
		static std::string
		staticEncode(const std::string &input);
};

#endif /* CHUNKENCODER_HPP_ */
