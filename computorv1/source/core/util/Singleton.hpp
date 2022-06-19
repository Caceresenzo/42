/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Singleton.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:00:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/05 21:00:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SINGLETON_HPP_
# define SINGLETON_HPP_

template<typename T>
	class Singleton
	{
		public:
			static T&
			get_instance(void)
			{
				static T instance;

				return (instance);
			}
	};

#endif /* SINGLETON_HPP_ */
