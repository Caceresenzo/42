/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 19:44:50 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 19:44:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_HPP_
# define OPTIONAL_HPP_

template<typename T>
	class Optional
	{
		private:
			bool m_has_value;
			T m_value;

		public:
			Optional() :
					m_has_value(false),
					m_value()
			{
			}

			Optional(const T &value) :
					m_has_value(true),
					m_value(value)
			{
			}

			Optional(const Optional<T> &right) :
					m_has_value(right.m_has_value),
					m_value(right.m_value)
			{
			}

		public:
			T
			get() const
			{
				return (m_value);
			}

			T
			or_else(const T &default_value) const
			{
				if (!m_has_value)
					return (default_value);

				return (m_value);
			}

			bool
			is_present() const
			{
				return (m_has_value);
			}

			bool
			is_absent() const
			{
				return (!m_has_value);
			}

		public:
			static Optional
			empty()
			{
				return (Optional());
			}

			static Optional
			of(const T &value)
			{
				return (Optional(value));
			}
	};

#endif /* OPTIONAL_HPP_ */
