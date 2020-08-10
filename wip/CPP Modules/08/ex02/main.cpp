/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:59:39 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 14:59:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <cstdlib>

#include "mutantstack.hpp"

#define xassert(exp) \
	{ \
		if ((exp)) \
			std::cout << "\e[92mPASSED\e[39m: " << #exp << std::endl; \
		else { \
			std::cout << "\e[91mFAILED\e[39m: " << #exp << "    (line: " << __LINE__ << ")" << std::endl; \
			exit(1); \
		} \
	}

int
main()
{
	std::cout << "--- TESTS ---" << std::endl;

	{
		MutantStack<int> mstack;

		xassert(mstack.size() == 0);

		for (int index = 0; index < 50; ++index)
			mstack.push(index);

		xassert(mstack.top() == 49);
		xassert(mstack.size() == 50);

		mstack.pop();
		xassert(mstack.top() == 48);
		xassert(mstack.size() == 49);

		unsigned long times = 0;
		for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
			times++;

		xassert(times == mstack.size());

		xassert(std::stack<int>(mstack).size() == mstack.size());
		xassert(std::stack<int>(mstack).top() == mstack.top());

		std::stack<int> copy(mstack);
		copy.pop();
		xassert(copy.size() != mstack.size());
		xassert(copy.top() != mstack.top());

		copy.push(15);
		xassert(copy.top() == 15);
		xassert(copy.size() == mstack.size());
	}

	std::cout << std::endl << "--- TESTS 42 ---" << std::endl;
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);

		std::cout << "top: " << mstack.top() << std::endl;

		std::cout << "size before pop: " << mstack.size() << std::endl;
		mstack.pop();
		std::cout << "size after pop: " << mstack.size() << std::endl;
		mstack.pop();
		std::cout << "size after pop: " << mstack.size() << std::endl;

		mstack.push(1);
		mstack.push(2);
		mstack.push(3);
		mstack.push(4);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;

		std::cout << "stack content: " << std::endl;
		while (it != ite)
		{
			std::cout << ">>> " << *it << std::endl;
			++it;
		}

		it = mstack.begin();
		ite = mstack.end();

		std::cout << "stack reversed content: " << std::endl;
		while (it != ite)
		{
			--ite;
			std::cout << ">>> " << *ite << std::endl;
		}

		std::stack<int> s(mstack);
		std::cout << "copying: are same size? "
		        << (s.size() == mstack.size() ? "yes" : "no")
		        << " (supposed to be yes)" << std::endl;
	}

	return (0);
}
