/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 11:35:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 11:35:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "span.hpp"

void
display_test_results(int n, Span &span)
{
	std::cout << "longest: " << span.longestSpan() << std::endl;
	std::cout << "shortest: " << span.shortestSpan() << std::endl;

	std::cout << "content: ";
	if (n <= 10000)
		span.dump();
	else
		std::cout << "[ not printed ]";
	std::cout << std::endl;
}

void
do_test(int n, int multiplier)
{
	std::cout << "--- TESTING n=" << n << ", m=" << multiplier << " ---" << std::endl;

	Span span(n);

	for (int index = 0; index < n; ++index)
		span.addNumber((index + 1) * multiplier);

	display_test_results(n, span);
}

void
do_test(int n, std::vector<int> vector)
{
	std::cout << "--- TESTING n=" << n << ", vector=" << vector.size() << " ---" << std::endl;

	Span span(n);
	span.addNumber(vector);

	display_test_results(n, span);
}

int
main(void)
{
	do_test(10, 2);
	do_test(100, 3);
	do_test(10000, 5);
	do_test(100000, 10);
	do_test(1000000, 15);

	std::vector<int> vector;
	for (int index = 0; index < 10; ++index)
		vector.push_back(index);

	do_test(10, vector);

	try
	{
		std::cout << "--- TESTING RANGE ---" << std::endl;

		Span span = Span(3);
		span.addNumber(5, 8);
		display_test_results(3, span);
	}
	catch (std::exception &e)
	{
		std::cout << "FAILED: " << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING RANGE - from > to ---" << std::endl;

		Span span = Span(3);
		span.addNumber(8, 5);
		display_test_results(3, span);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING RANGE - from = to ---" << std::endl;

		Span span = Span(3);
		span.addNumber(5, 5);
		display_test_results(3, span);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=0, but adding one ---" << std::endl;

		Span zero = Span(0);
		zero.addNumber(0);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=1, but adding one ---" << std::endl;

		Span zero = Span(1);
		zero.addNumber(1);
		zero.addNumber(2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=0, but adding vector (5) ---" << std::endl;

		Span zero = Span(0);

		std::vector<int> vector2;
		for (int index = 0; index < 5; ++index)
			vector2.push_back(index);

		zero.addNumber(vector2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=0, shortest ---" << std::endl;

		Span(0).shortestSpan();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=0, longest ---" << std::endl;

		Span(0).longestSpan();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=1, shortest ---" << std::endl;

		Span span(1);
		span.addNumber(1);

		span.shortestSpan();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	try
	{
		std::cout << "--- TESTING n=1, longest ---" << std::endl;

		Span span(1);
		span.addNumber(1);

		span.longestSpan();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl << std::endl;
	}

	std::cout << "--- TESTING 42 ---" << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(5);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
}
