/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:37:54 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 18:37:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP_
# define SPAN_HPP_

# include <exception>
# include <iostream>
# include <vector>

class Span
{
	private:
		unsigned int _n;
		std::vector<int> _vector;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span &other);

		virtual ~Span();

		Span& operator=(const Span &other);

		void addNumber(int number);
		void addNumber(std::vector<int> const &numbers);
		void addNumber(int from, int to);
		void addNumber(Span const &other);

		int shortestSpan() const;
		int longestSpan() const;

		void dump();

		class SpanException : public std::exception
		{
			private:
				const std::string _message;

			public:
				SpanException(void);
				SpanException(std::string message);
				SpanException(const SpanException &other);

				virtual ~SpanException(void) throw ();

				SpanException& operator=(const SpanException &other);

				virtual const char* what() const throw ();

				const std::string &message() const;

				static SpanException illegalArgument();
				static SpanException capacityReached();
				static SpanException requireAtLeast2();
		};
};

#endif /* SPAN_HPP_ */
