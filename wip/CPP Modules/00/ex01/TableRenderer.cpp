/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TableRenderer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>

#include "TableRenderer.hpp"

const int TableRenderer::columnWidth = 10;
const char TableRenderer::separator = '|';
const char TableRenderer::truncateChar = '.';

void
TableRenderer::renderColumnEntry(std::string text)
{
	size_t length = text.length();

	if (length >= TableRenderer::columnWidth)
	{
		bool tooLong = length > TableRenderer::columnWidth;

		text = text.substr(0, TableRenderer::columnWidth - (tooLong ? 1 : 0));

		if (tooLong)
			text += truncateChar;
	}

	std::cout << std::setfill(' ') << std::setw(TableRenderer::columnWidth);
	std::cout << text;
	std::cout << std::setfill(' ') << std::setw(0);
}

void
TableRenderer::renderBorder(bool end)
{
	if (end)
		std::cout << std::endl;
	else
		std::cout << TableRenderer::separator;
}
