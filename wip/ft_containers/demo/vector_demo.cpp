/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_demo.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:17:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 18:17:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>

int
main(void)
{
	typedef ft::Vector<std::string> Vec;
	Vec v;

	v.push_back("Hello");
	v.push_back("World");
	v.push_back("From");
	v.push_back("Vectors");

	const Vec cv = v;

	for (Vec::const_iterator it = cv.begin(); it < cv.end(); it++)
		std::cout << *it << " (length of: " << it->size() << ")" << std::endl;

	std::cout << std::endl;

	for (Vec::const_reverse_iterator rit = cv.rbegin(); rit < cv.rend(); rit++)
		std::cout << *rit << " (length of: " << rit->size() << ")" << std::endl;
}
