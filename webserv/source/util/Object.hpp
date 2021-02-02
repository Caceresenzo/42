/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:20:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/06 22:20:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_HPP_
# define OBJECT_HPP_

#include <string>

class Object
{
	public:
		Object();
		Object(const Object &other);

		virtual
		~Object();

		Object&
		operator=(const Object &other);

		virtual std::string
		toString() const;
};

#endif /* OBJECT_HPP_ */
