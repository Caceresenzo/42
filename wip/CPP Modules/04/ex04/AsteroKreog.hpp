/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsteroKreog.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:59:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:59:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTEROKREOG_HPP_
# define ASTEROKREOG_HPP_

#include "IAsteroid.hpp"

class AsteroKreog : public IAsteroid
{
	public:
		AsteroKreog();
		AsteroKreog(const AsteroKreog &other);

		virtual ~AsteroKreog();

		AsteroKreog& operator=(const AsteroKreog &other);

		virtual std::string beMined(DeepCoreMiner*) const;
		virtual std::string beMined(StripMiner*) const;

		virtual std::string getName() const;
};

#endif /* ASTEROKREOG_HPP_ */
