/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:54:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/01 11:54:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Another.hpp"

void
identify_from_pointer(Base *p)
{
	char *type = NULL;

	try
	{
		if (!p)
			type = (char *) "null ptr";
		if (dynamic_cast<A*>(p))
			type = (char *) "A";
		else if (dynamic_cast<B*>(p))
			type = (char *) "B";
		else if (dynamic_cast<C*>(p))
			type = (char *) "C";
		else if (dynamic_cast<Base*>(p))
			type = (char *) "Base";
	}
	catch (std::exception &e)
	{
	}

	if (type == NULL)
		type = (char *) "unknown type";

	std::cout << type << std::endl;
}

void
identify_from_reference(Base &p)
{
	identify_from_pointer(&p);
}

int
main(void)
{
	Base base;
	A a;
	B b;
	C c;
	Another another;

	std::cout << "-- from pointer --" << std::endl;
	identify_from_pointer(&base);
	identify_from_pointer(&a);
	identify_from_pointer(&b);
	identify_from_pointer(&c);

	std::cout << std::endl << "-- from reference --" << std::endl;
	identify_from_reference(base);
	identify_from_reference(a);
	identify_from_reference(b);
	identify_from_reference(c);

	std::cout << std::endl << "-- a NULL pointer --" << std::endl;
	identify_from_pointer(NULL);

	std::cout << std::endl << "-- an unreleated (but casted) value --" << std::endl;
	identify_from_pointer((Base*)((void*)&another));
}
