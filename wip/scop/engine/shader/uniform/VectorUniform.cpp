/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorUniform.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:33:30 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:33:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/uniform/VectorUniform.hpp>

template<>
	void
	VectorUniform<2, int>::set(const Vector<2, int> &vector)
	{
		glUniform2i(location(), vector.x, vector.y);
	}

template<>
	void
	VectorUniform<3, float>::set(const Vector<3, float> &vector)
	{
		glUniform3f(location(), vector.x, vector.y, vector.z);
	}
