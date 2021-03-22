/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_demo.cpp                                     :+:      :+:    :+:   */
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
#include "Queue.hpp"

int
main(void)
{
	typedef ft::Queue<std::string> Que;
	Que q;

	q.push("Hello");
	q.push("World");
	q.push("From");
	q.push("Queues");

	std::cout << "top? " << q.front() << std::endl;
	std::cout << "back? " << q.back() << std::endl << std::endl;

	q.pop();

	std::cout << "top? " << q.front() << std::endl;
	std::cout << "back? " << q.back() << std::endl << std::endl;

	q.pop();

	std::cout << "top? " << q.front() << std::endl;
	std::cout << "back? " << q.back() << std::endl << std::endl;

	q.pop();

	std::cout << "top? " << q.front() << std::endl;
	std::cout << "back? " << q.back() << std::endl << std::endl;

	q.pop();

	std::cout << "final size? " << q.size() << std::endl;
}
