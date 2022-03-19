/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MeshException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:59:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 20:59:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESHEXCEPTION_HPP_
# define MESHEXCEPTION_HPP_

#include <lang/RuntimeException.hpp>
#include <string>

class MeshException :
		public RuntimeException
{
	public:
		MeshException();
		MeshException(const std::string &message);
		MeshException(const MeshException &other);

		virtual
		~MeshException() throw ();

		MeshException&
		operator=(const MeshException &other);
};

#endif /* MESHEXCEPTION_HPP_ */
