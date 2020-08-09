/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IAsteroid.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:49:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:49:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IASTEROID_HPP_
# define IASTEROID_HPP_

# include <iostream>

class DeepCoreMiner;
class StripMiner;

class IAsteroid
{
	public:
		virtual ~IAsteroid() { }

		virtual std::string beMined(DeepCoreMiner*) const = 0;
		virtual std::string beMined(StripMiner*) const = 0;

		virtual std::string getName() const = 0;
};

#endif /* IASTEROID_HPP_ */
