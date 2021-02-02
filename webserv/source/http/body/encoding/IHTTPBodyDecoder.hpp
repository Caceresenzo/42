/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHTTPBodyDecoder.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:00:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/10 10:57:10 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IHTTPBODYDECODER_HPP_
# define IHTTPBODYDECODER_HPP_

#include <string>

class IHTTPBodyDecoder
{
	public:
		virtual
		~IHTTPBodyDecoder();

		/**
		 * Consume a character.
		 *
		 * @param in Input data.
		 * @param out Output storage.
		 * @return Consumed character, if the number is 0, that mean that no character has been consumed and the body has been fully read.
		 */
		virtual bool
		consume(const std::string &in, std::string &out, size_t &consumed, bool max) = 0;

		std::string
		decode(const std::string &input, bool max);

		/**
		 * Cleanup the memory after usage.
		 *
		 * For stateful and allocated, that mean delete-ing itself.
		 * For stateless, nothing is done.
		 */
		virtual void
		cleanup();

		
};

#endif /* IHTTPBODYDECODER_HPP_ */
