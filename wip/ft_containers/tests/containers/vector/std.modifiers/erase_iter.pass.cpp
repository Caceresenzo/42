/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_iter.pass.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 20:09:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/26 20:09:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <test_macros.hpp>
//
//#ifndef TEST_HAS_NO_EXCEPTIONS
//struct Throws
//{
//		Throws() :
//		        v_(0)
//		{
//		}
//		Throws(int v) :
//		        v_(v)
//		{
//		}
//		Throws(const Throws &rhs) :
//		        v_(rhs.v_)
//		{
//			if (sThrows)
//				throw 1;
//		}
//		Throws(Throws &&rhs) :
//		        v_(rhs.v_)
//		{
//			if (sThrows)
//				throw 1;
//		}
//		Throws&
//		operator=(const Throws &rhs)
//		{
//			v_ = rhs.v_;
//			return *this;
//		}
//		Throws&
//		operator=(Throws &&rhs)
//		{
//			v_ = rhs.v_;
//			return *this;
//		}
//		int v_;
//		static bool sThrows;
//};
//
//bool Throws::sThrows = false;
//#endif

int
main(void)
{
	{
		int a1[] = { 1, 2, 3 };
//		ft::Vector<int> l1(a1, a1 + 3);
		ft::Vector<int> l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);

		ft::Vector<int>::iterator i = l1.begin();
		++i;
		ft::Vector<int>::iterator j = l1.erase(i);
		ASSERT(l1.size() == 2);
		ASSERT(*j == 3);
		ASSERT(*l1.begin() == 1);
		ASSERT(*(l1.begin() + 1) == 3);
		j = l1.erase(j);
		ASSERT(j == l1.end());
		ASSERT(l1.size() == 1);
		ASSERT(*l1.begin() == 1);
		j = l1.erase(l1.begin());
		ASSERT(j == l1.end());
		ASSERT(l1.size() == 0);
	}
//#ifndef TEST_HAS_NO_EXCEPTIONS
//// Test for LWG2853:
//// Throws: Nothing unless an exception is thrown by the assignment operator or move assignment operator of T.
//	{
////		Throws arr[] = { 1, 2, 3 };
////		ft::Vector<Throws> v(arr, arr + 3);
//		ft::Vector<Throws> v;
//		v.push_back(Throws(1));
//		v.push_back(Throws(2));
//		v.push_back(Throws(3));
//
//		Throws::sThrows = true;
//		v.erase(v.begin());
//		v.erase(--v.end());
//		v.erase(v.begin());
//		ASSERT(v.size() == 0);
//	}
//#endif

	return 0;
}
