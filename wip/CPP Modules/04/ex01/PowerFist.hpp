/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:28:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 17:28:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWERFIST_HPP_
# define POWERFIST_HPP_

#include "AWeapon.hpp"

class PowerFist : public AWeapon
{
	public:
		PowerFist();
		PowerFist(const PowerFist &other);

		virtual
		~PowerFist();

		PowerFist& operator=(const PowerFist &other);

		virtual void attack() const;
};

#endif /* POWERFIST_HPP_ */
