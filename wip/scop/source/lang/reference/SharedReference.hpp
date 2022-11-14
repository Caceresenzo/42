/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SharedReference.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:40:39 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/12 20:40:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAREDREFERENCE_HPP_
# define SHAREDREFERENCE_HPP_

#include <lang/reference/ReferenceCounter.hpp>
#include <lang/reference/WeakReference.hpp>
#include <cassert>
#include <iostream>
#include <string>

template<typename T>
	class WeakReference;

template<typename T>
	class SharedReference
	{
		private:
			ReferenceCounter *m_counter;
			T *m_value;

		public:
			SharedReference() :
				m_counter(NULL),
				m_value(NULL)
			{
			}

			SharedReference(T &value) :
				m_counter(new ReferenceCounter()),
				m_value(&value)
			{
				add();
			}

			SharedReference(const SharedReference &other) :
				m_counter(other.m_counter),
				m_value(other.m_value)
			{
				/* if no value, then no counter either */
				assert(!m_value == !m_counter);

				add();
			}

			~SharedReference()
			{
				release();

				assert(m_value == NULL);
				assert(m_counter == NULL);
			}

		public:
			SharedReference&
			operator=(const SharedReference &other)
			{
				if (this != &other)
				{
					release();

					m_counter = other.m_counter;
					m_value = other.m_value;

					add();
				}

				return (*this);
			}

			T&
			operator*()
			{
				return (*m_value);
			}

			const T&
			operator*() const
			{
				return (*m_value);
			}

			T*
			operator->()
			{
				return (m_value);
			}

			const T*
			operator->() const
			{
				return (m_value);
			}

			operator bool() const
			{
				return (!!m_value);
			}

		public:
			T*
			value()
			{
				return (m_value);
			}

			const T*
			value() const
			{
				return (m_value);
			}

			long
			count()
			{
				if (m_counter)
					return (m_counter->get_shared());

				return (0);
			}

			void
			release()
			{
				if (m_value)
				{
					assert(!!m_counter);

					if (m_counter->release_shared() == 0)
						delete m_value;

					if (m_counter->get() == 0)
						delete m_counter;
				}

				m_value = NULL;
				m_counter = NULL;
			}

			void
			add()
			{
				if (!m_value)
					return;

				if (!m_counter)
					m_counter = new ReferenceCounter();

				m_counter->add_shared();
			}

		public:
			friend class WeakReference<T> ;
	};

#endif /* SHAREDREFERENCE_HPP_ */
