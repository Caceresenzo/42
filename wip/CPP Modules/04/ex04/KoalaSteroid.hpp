/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KoalaSteroid.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:59:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:59:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KOALASTEROID_HPP_
# define KOALASTEROID_HPP_

#include "IAsteroid.hpp"

class KoalaSteroid : public IAsteroid
{
	public:
		KoalaSteroid();
		KoalaSteroid(const KoalaSteroid &other);

		virtual ~KoalaSteroid();

		KoalaSteroid& operator=(const KoalaSteroid &other);

		virtual std::string beMined(DeepCoreMiner*) const;
		virtual std::string beMined(StripMiner*) const;

		virtual std::string getName() const;
};

#endif /* KOALASTEROID_HPP_ */
