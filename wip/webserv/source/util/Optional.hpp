/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Optional.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:31:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/22 16:18:54 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONAL_HPP_
# define OPTIONAL_HPP_

#include <exception/Exception.hpp>
#include <stddef.h>
#include <util/TypeTraits.hpp>

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

			Optional(T &value) :
					m_present(true),
					m_value(value)
			{
			}

			Optional(const T &value) :
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

			Optional&
			operator=(T &value)
			{
				m_present = true;
				m_value = value;

				return (*this);
			}

			bool
			present() const
			{
				return (m_present);
			}

			bool
			absent() const
			{
				return (!m_present);
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
			set(void)
			{
				m_present = true;

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

			template<typename U>
				bool
				equals(const U &other) const
				{
					if (m_present)
						return (m_value == other);

					return (false);
				}

			T&
			orElse(const T &defaultValue)
			{
				if (m_present)
					return (m_value);

				return (defaultValue);
			}

			const T&
			orElse(const T &defaultValue) const
			{
				if (m_present)
					return (m_value);

				return (defaultValue);
			}

			Optional<T>&
			otherwise(Optional<T> &optional)
			{
				if (m_present)
					return (*this);

				return (optional);
			}

			const Optional<T>&
			otherwise(const Optional<T> &optional) const
			{
				if (m_present)
					return (*this);

				return (optional);
			}

		public:
			static Optional<T>
			onlyIf(bool present, T &value)
			{
				if (present)
					return (Optional(value));

				return (Optional());
			}

			static Optional<T>
			onlyIf(bool present, const T &value)
			{
				if (present)
					return (Optional(value));

				return (Optional());
			}

			static Optional<T>
			ofNullable(T &value)
			{
				if (value != NULL)
					return (Optional(value));

				return (Optional());
			}

			static Optional<T>
			ofNullable(const T &value)
			{
				if (value != NULL)
					return (Optional(value));

				return (Optional());
			}

			static Optional<T>
			ofEmpty(T &value)
			{
				if (!value.empty())
					return (Optional(value));

				return (Optional());
			}

			static Optional<T>
			ofEmpty(const T &value)
			{
				if (!value.empty())
					return (Optional(value));

				return (Optional());
			}
	};

#endif /* OPTIONAL_HPP_ */
