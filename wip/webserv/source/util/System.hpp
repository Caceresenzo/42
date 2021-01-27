/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   System.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 20:48:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/29 20:48:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSTEM_HPP_
# define SYSTEM_HPP_

class System
{
	private:
		System();
		System(const System &other);

		virtual
		~System();

		System&
		operator =(const System &other);

	public:
		static unsigned long
		currentTimeSeconds(void);
};

#endif /* SYSTEM_HPP_ */
