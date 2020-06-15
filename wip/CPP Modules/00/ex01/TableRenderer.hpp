/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TableRenderer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLERENDERER_HPP
# define TABLERENDERER_HPP

# include <string>

class TableRenderer
{
	private:
		const static int columnWidth;
		const static char separator;
		const static char truncateChar;

	public:
		static void renderColumnEntry(std::string text);
		static void renderBorder(bool end);
};

#endif /* TABLERENDERER_HPP_ */
