/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KoalaSteroid.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:59:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:59:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KoalaSteroid.hpp"

KoalaSteroid::KoalaSteroid()
{
}

KoalaSteroid::KoalaSteroid(const KoalaSteroid &other)
{
	operator =(other);
}

KoalaSteroid::~KoalaSteroid()
{
}

KoalaSteroid&
KoalaSteroid::operator=(const KoalaSteroid &other)
{
	(void)other;

	return (*this);
}

std::string
KoalaSteroid::beMined(DeepCoreMiner*) const
{
	return ("Mithril");
}

std::string
KoalaSteroid::beMined(StripMiner*) const
{
	return ("Tartarite");
}

std::string
KoalaSteroid::getName() const
{
	return ("koala");
}
