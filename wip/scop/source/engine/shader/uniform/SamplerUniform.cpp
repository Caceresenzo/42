/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SamplerUniform.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 01:35:44 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/03 01:35:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine/shader/ShaderVariable.hpp>
#include <engine/shader/uniform/SamplerUniform.hpp>

template<>
	void
	SamplerUniform<int>::set(const int &sampler)
	{
		glUniform1i(location(), sampler);
	}
