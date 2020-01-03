/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Pony.hpp"

void
printAddress(Pony *ptr)
{
	int aVariableOnTheStack = 0;

	std::cout << "\e[1m";
	std::cout << "PTR LOCAL VARIABLE : " << (void *) &aVariableOnTheStack << std::endl;
	std::cout << "PTR IN PARAMETER   : " << (void *) ptr << std::endl;
	std::cout << "\e[0m";
}

void
ponyOnTheStack(void)
{
	Pony pony("Stacker", c_white);

	pony.tellName();
	pony.tellColor();
	pony.changeColor(c_black);
	pony.tellColor();

	printAddress(&pony);
}

void
ponyOnTheHeap(void)
{
	Pony *pony = new Pony("Heaper", c_white);

	pony->tellName();
	pony->tellColor();
	pony->changeColor(c_brown);
	pony->tellColor();

	printAddress(pony);

	delete pony;

	// pony->tellName();
	// pony->tellColor();
}

int
main(void) {
	std::cout << "--- ponyOnTheStack()" << std::endl;
	ponyOnTheStack();

	std::cout << "--- ponyOnTheHeap()" << std::endl;
	ponyOnTheHeap();

	return (0);
}
