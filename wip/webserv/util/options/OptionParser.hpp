/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OptionParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:36:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 19:36:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONPARSER_HPP_
# define OPTIONPARSER_HPP_

class OptionParser
{
	public:
		OptionParser();
		OptionParser(const OptionParser &other);

		virtual
		~OptionParser();

		OptionParser&
		operator=(const OptionParser &other);
};

#endif /* OPTIONPARSER_HPP_ */
