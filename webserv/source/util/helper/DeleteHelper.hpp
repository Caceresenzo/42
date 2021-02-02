/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeleteHelper.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 01:47:31 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/17 01:47:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETEHELPER_HPP_
# define DELETEHELPER_HPP_

#include <util/Optional.hpp>
#include <list>

class DeleteHelper
{
	private:
		DeleteHelper();
		DeleteHelper(const DeleteHelper &other);

		virtual
		~DeleteHelper();

		DeleteHelper&
		operator=(const DeleteHelper &other);

	public:
		template<typename T>
			static void
			pointers2(T **arr)
			{
				T **start = arr;

				if (arr)
				{
					T *ptr;
					while ((ptr = *arr++))
						if (ptr)
							delete[] ptr;

					delete[] start;
				}
			}

		template<typename T>
			static void
			pointers(Optional<std::list<T*> > &optional)
			{
				if (optional.present())
				{
					pointers(optional.get());
					optional.unset();
				}
			}

		template<typename T>
			static void
			pointers(Optional<std::list<T const*> > &optional)
			{
				if (optional.present())
				{
					pointers(optional.get());
					optional.unset();
				}
			}

		template<typename T>
			static void
			pointers(std::list<T*> &blocks)
			{
				for (typename std::list<T*>::iterator it = blocks.begin(); it != blocks.end(); it++)
					delete *it;

				blocks.clear();
			}

		template<typename T>
			static void
			pointers(std::list<T const*> &blocks)
			{
				for (typename std::list<T const*>::iterator it = blocks.begin(); it != blocks.end(); it++)
					delete *it;

				blocks.clear();
			}

		template<typename T>
			static void
			pointer(Optional<T*> &optional)
			{
				if (optional.present())
				{
					pointer(optional.get());
					optional.unset();
				}
			}

		template<typename T>
			static void
			pointer(Optional<T const*> &optional)
			{
				if (optional.present())
				{
					pointer(optional.get());
					optional.unset();
				}
			}

		template<typename T>
			static void
			pointer(T *&ptr)
			{
				if (ptr)
					delete ptr;

				ptr = NULL;
			}

		template<typename T>
			static void
			pointer(T const *&ptr)
			{
				if (ptr)
					delete ptr;

				ptr = NULL;
			}
};

#endif /* DELETEHELPER_HPP_ */
