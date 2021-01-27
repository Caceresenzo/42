/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonUtils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:18:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:18:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONUTILS_HPP_
# define JSONUTILS_HPP_

#include <string>

class JsonUtils
{
	private:
		JsonUtils();
		JsonUtils(const JsonUtils &other);

		virtual
		~JsonUtils();

		JsonUtils&
		operator=(const JsonUtils &other);

	public:
		static std::string
		escapeString(const std::string &str);

		static std::string
		escapeHex(char c);
};

#endif /* JSONUTILS_HPP_ */
