/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BooleanUniform.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 13:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOOLEANUNIFORM_HPP_
# define BOOLEANUNIFORM_HPP_

#include <engine/shader/uniform/Uniform.hpp>
#include <string>

class BooleanUniform :
		public Uniform
{
	public:
		BooleanUniform(const std::string &name);

	public:
		void
		set(bool value);
};

#endif /* BooleanUniform_HPP_ */
