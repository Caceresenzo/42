/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IHTTPBodyEncoder.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:06:44 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/09 01:06:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IHTTPBODYENCODER_HPP_
# define IHTTPBODYENCODER_HPP_

#include <string>

class IHTTPBodyEncoder
{
	public:
		virtual
		~IHTTPBodyEncoder();

		/**
		 * Encode a string.
		 *
		 * @param input Data to encode.
		 * @return Encoded data.
		 */
		virtual std::string
		encode(const std::string &input) = 0;

		/**
		 * Cleanup the memory after usage.
		 *
		 * For stateful and allocated, that mean delete-ing itself.
		 * For stateless, nothing is done.
		 */
		virtual void
		cleanup();
};

#endif /* IHTTPBODYENCODER_HPP_ */
