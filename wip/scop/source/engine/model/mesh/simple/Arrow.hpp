/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arrow.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 02:18:21 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/04 02:18:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARROW_HPP_
# define ARROW_HPP_

class Mesh;

class Arrow
{
	public:
		static Mesh*
		of(float length = 100.0f);
};

#endif /* ARROW_HPP_ */
