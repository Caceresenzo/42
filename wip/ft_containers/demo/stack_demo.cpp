/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_demo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:17:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 18:17:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Iterator.hpp"
#include "Stack.hpp"

int
main(void)
{
	typedef ft::Stack<std::string> Stk;
	Stk s;

	s.push("Hello");
	s.push("World");
	s.push("From");
	s.push("Stacks");

	std::cout << "top? " << s.top() << std::endl;

	s.pop();

	std::cout << "top? " << s.top() << std::endl;

	s.pop();

	std::cout << "top? " << s.top() << std::endl;

	s.pop();

	std::cout << "top? " << s.top() << std::endl;

	s.pop();

	std::cout << "final size? " << s.size() << std::endl;
}
