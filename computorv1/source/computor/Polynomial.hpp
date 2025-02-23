/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polynomial.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:23:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 19:23:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYNOMIAL_HPP_
# define POLYNOMIAL_HPP_

#include <core/lang/Number.hpp>
#include <core/util/Iterator.hpp>
#include <core/util/Optional.hpp>
#include <iostream>
#include <map>
#include <set>

template<typename V = long double, typename E = int>
	class Polynomial
	{
		public:
			typedef V value_type;
			typedef E exponent_type;
			typedef std::map<E, V> map;
			typedef typename map::const_iterator const_iterator;

		private:
			map m_values;

		public:
			Polynomial() :
					m_values()
			{
			}

			Polynomial(const map &values) :
					m_values(values)
			{
			}

		public:
			Optional<V>
			find(const E &exponent) const
			{
				const_iterator iterator = m_values.find(exponent);

				if (iterator == end())
					return Optional<V>::empty();

				return (Optional<V>::of(iterator->second));
			}

			const_iterator
			begin() const
			{
				return (m_values.begin());
			}

			const_iterator
			end() const
			{
				return (m_values.end());
			}

		public:
			std::set<E>
			exponents() const
			{
				std::set<E> keys;

				for (const_iterator iterator = begin(); iterator != end(); ++iterator)
					keys.insert(iterator->first);

				return (keys);
			}

		public:
			E
			degree() const
			{
				if (m_values.empty())
					return (-1);

				const_iterator iterator = begin();
				E exponent = iterator->first;

				for (; iterator != end(); ++iterator)
					if (iterator->second)
						exponent = std::max(exponent, iterator->first);

				return (exponent);
			}

		public:
			static Polynomial
			reduce(Polynomial left, Polynomial right)
			{
				map values;

				std::set<E> right_keys = right.exponents();
				std::set<E> left_keys = left.exponents();

				std::set<E> keys = right.exponents();
				keys.insert(right_keys.begin(), right_keys.end());
				keys.insert(left_keys.begin(), left_keys.end());

				typedef typename std::set<E>::const_iterator set_const_iterator;
				for (set_const_iterator iterator = keys.begin(); iterator != keys.end(); ++iterator)
				{
					const E &exponent = *iterator;

					Optional<V> left_value = left.find(exponent);
					Optional<V> right_value = right.find(exponent);

					if (left_value.is_absent() && right_value.is_absent())
						continue;

					V value = V();

					if (left_value.is_present())
						value += left_value.get();

					if (right_value.is_present())
						value -= right_value.get();

					values[exponent] = value;
				}

//				for (const_iterator iterator = values.begin(); iterator != values.end(); ++iterator)
//				{
//					if (iterator->second == 0)
//						values.erase(iterator->first);
//				}

				return (Polynomial(values));
			}

		public:
			static Polynomial
			zero()
			{
				return (Polynomial());
			}

			static Polynomial
			constant(const V &a)
			{
				map values;

				if (a)
					values[0] = a;

				return (Polynomial(values));
			}

			static Polynomial
			linear(const V &a, const V &b)
			{
				map values;
				values[1] = a;
				values[0] = b;

				return (Polynomial(values));
			}

			static Polynomial
			quadratic(const V &a, const V &b, const V &c)
			{
				map values;
				values[2] = a;
				values[1] = b;
				values[0] = c;

				return (Polynomial(values));
			}

			static Polynomial
			cubic(const V &a, const V &b, const V &c, const V &d)
			{
				map values;
				values[3] = a;
				values[2] = b;
				values[1] = c;
				values[0] = d;

				return (Polynomial(values));
			}

		public:
			template<typename VV, typename EE>
				friend bool
				operator==(const Polynomial<VV, EE> &left, const Polynomial<VV, EE> &right);
	};

template<typename V, typename E>
	bool
	operator==(const Polynomial<V, E> &left, const Polynomial<V, E> &right)
	{
		return (left.m_values == right.m_values);
	}

template<typename V, typename E>
	std::ostream&
	operator <<(std::ostream &stream, const Polynomial<V, E> &polynomial)
	{
		typedef typename Polynomial<V, E>::const_iterator const_iterator;

		const_iterator iterator = polynomial.begin();

		if (iterator == polynomial.end())
			return (stream << "0");

		bool first = false;

		for (; iterator != polynomial.end(); ++iterator)
		{
			V value = iterator->second;

			if (first)
				value = Number::abs(value);

			stream << Number::to_string(value) << " * X^" << Number::to_string(iterator->first);

			const_iterator next = Iterator::next(iterator);
			if (next == polynomial.end())
				stream << " = 0";
			else
			{
				if (next->second < 0)
					stream << " - ";
				else
					stream << " + ";
			}

			if (!first)
				first = true;
		}

		return (stream);
	}

#endif /* POLYNOMIAL_HPP_ */
