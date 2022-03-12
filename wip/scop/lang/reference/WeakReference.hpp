/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WeakReference.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:41:53 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/12 20:41:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAKREFERENCE_HPP_
# define WEAKREFERENCE_HPP_

#include <ref/ReferenceCounter.hpp>
#include <ref/SharedReference.hpp>
#include <cassert>
#include <string>

template<typename T>
	class SharedReference;

template<typename T>
	class WeakReference
	{
		private:
			ReferenceCounter *m_counter;
			T *m_value;

		public:
			WeakReference() :
					m_counter(NULL),
					m_value(NULL)
			{
			}

			WeakReference(T &value) :
					m_counter(new ReferenceCounter()),
					m_value(&value)
			{
				add();
			}

			WeakReference(SharedReference<T> reference) :
					m_counter(reference.m_counter),
					m_value(reference.m_value)
			{
				add();
			}

			WeakReference(const WeakReference &other) :
					m_counter(other.m_counter),
					m_value(other.m_value)
			{
				/* if no value, then no counter either */
				assert(!m_value == !m_counter);

				add();
			}

			~WeakReference()
			{
				release();
			}

		public:
			WeakReference&
			operator=(const WeakReference &other)
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

			WeakReference&
			operator=(const SharedReference<T> &other)
			{
				release();

				m_counter = other.m_counter;
				m_value = other.m_value;

				add();

				return (*this);
			}

			T&
			operator*()
			{
				return (*m_value);
			}

			T*
			operator->()
			{
				return (m_value);
			}

		public:
			long
			count()
			{
				if (m_counter)
					return (m_counter->get_weak());

				return (0);
			}

			void
			release()
			{
				if (m_value)
				{
					assert(!!m_counter);

					m_counter->release_weak();

					if (m_counter->get() == 0)
						delete m_counter;
				}

				m_value = NULL;
				m_counter = NULL;
			}

			bool
			is_expired()
			{
				if (m_counter)
					return (m_counter->get_shared() == 0);

				return (true);
			}

		private:
			void
			add()
			{
				if (!m_value)
					return;

				if (!m_counter)
					m_counter = new ReferenceCounter();

				m_counter->add_weak();
			}
	};

#endif /* WEAKREFERENCE_HPP_ */
