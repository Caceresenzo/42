/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:31:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 16:31:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_HPP_
# define OPTIONAL_HPP_

#include <exception/Exception.hpp>

template<typename T>
	class Optional
	{
		private:
			bool m_present;
			T m_value;

		public:
			Optional(void) :
					m_present(false),
					m_value()
			{
			}

			Optional(T value) :
					m_present(true),
					m_value(value)
			{
			}

			Optional(const Optional &other) :
					m_present(other.m_present),
					m_value(other.m_value)
			{
			}

			virtual
			~Optional()
			{
			}

			Optional&
			operator=(const Optional &other)
			{
				if (this != &other)
				{
					m_present = other.m_present;
					m_value = other.m_value;
				}

				return (*this);
			}

			bool
			present() const
			{
				return (m_present);
			}

			Optional&
			ensurePresent()
			{
				if (!m_present)
					throw Exception("value not present");

				return (*this);
			}

			const Optional&
			ensurePresent() const
			{
				if (!m_present)
					throw Exception("value not present");

				return (*this);
			}

			Optional&
			set(const T &value)
			{
				m_present = true;
				m_value = value;

				return (*this);
			}

			Optional&
			unset(void)
			{
				m_present = false;

				return (*this);
			}

			T&
			get(void)
			{
				ensurePresent();

				return (m_value);
			}

			const T&
			get(void) const
			{
				ensurePresent();

				return (m_value);
			}

			T&
			orElse(const T &value)
			{
				if (m_present)
					return (m_value);

				return (value);
			}

			const T&
			orElse(const T &value) const
			{
				if (m_present)
					return (m_value);

				return (value);
			}
	};

#endif /* OPTIONAL_HPP_ */
