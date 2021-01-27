/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CustomErrorMap.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 23:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/16 23:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOMERRORMAP_HPP_
# define CUSTOMERRORMAP_HPP_

#include <map>
#include <string>

class HTTPStatus;

class CustomErrorMap
{
	public:
		typedef std::map<int, std::string> map;

	private:
		map m_storage;

	public:
		CustomErrorMap(void);
		CustomErrorMap(map storage);
		CustomErrorMap(const CustomErrorMap &other);

		virtual
		~CustomErrorMap(void);

		CustomErrorMap&
		operator=(const CustomErrorMap &other);

		bool
		has(int status) const;

		bool
		has(const HTTPStatus &status) const;

		const std::string&
		get(int status) const;

		const std::string&
		get(const HTTPStatus &status) const;
};

#endif /* CUSTOMERRORMAP_HPP_ */
