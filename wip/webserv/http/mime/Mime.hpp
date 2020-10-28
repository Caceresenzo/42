/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mime.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:37:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/26 17:37:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIME_HPP_
# define MIME_HPP_

# include <iostream>
# include <string>
# include <list>

class Mime
{
	public:
		typedef std::string string;
		typedef std::list<std::string> list;
		typedef list::const_iterator iterator;

	private:
		string m_type;
		list m_extensions;

	public:
		Mime();
		Mime(const string &type, const string &extension);
		Mime(const string &type, const list &extensions);
		Mime(const Mime &other);

		Mime&
		operator =(const Mime &other);

		const string&
		type() const;

		const list&
		extensions() const;
};

#endif /* MIME_HPP_ */
