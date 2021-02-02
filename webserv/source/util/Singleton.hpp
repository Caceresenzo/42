/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Singleton.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 19:56:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/24 19:56:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINGLETON_HPP_
# define SINGLETON_HPP_

template<typename T>
	class Singleton
	{
		public:
			static T&
			instance(void)
			{
				static T instance;

				return (instance);
			}
	};

#endif /* SINGLETON_HPP_ */
