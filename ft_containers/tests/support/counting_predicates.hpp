/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting_predicates.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 22:22:04 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/08 22:22:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNTING_PREDICATES_H
# define COUNTING_PREDICATES_H

template<typename Predicate, typename Arg>
	struct unary_counting_predicate
	{
		public:
			typedef Arg argument_type;
			typedef bool result_type;

		private:
			Predicate m_predicate;
			unsigned long m_count;

		public:
			unary_counting_predicate(Predicate predicate) :
					m_predicate(predicate),
					m_count(0)
			{
			}

			~unary_counting_predicate()
			{
			}

			bool
			operator ()(const Arg &input)
			{
				++m_count;
				return (m_predicate(input));
			}

			unsigned long
			count() const
			{
				return (m_count);
			}

			void
			reset()
			{
				m_count = 0;
			}
	};

template<typename Predicate, typename Arg>
	struct delegated_unary_counting_predicate
	{
		public:
			typedef Arg argument_type;
			typedef bool result_type;

		private:
			Predicate m_predicate;
			unsigned long *m_count;

		public:
			delegated_unary_counting_predicate(Predicate predicate, unsigned long *count) :
					m_predicate(predicate),
					m_count(count)
			{
			}

			~delegated_unary_counting_predicate()
			{
			}

			bool
			operator ()(const Arg &input)
			{
				*m_count += 1;
				return (m_predicate(input));
			}

			unsigned long
			count() const
			{
				return (*m_count);
			}

			void
			reset()
			{
				*m_count = 0;
			}
	};

#endif
