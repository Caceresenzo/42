/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objects.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:18:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/11 21:18:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_HPP_
# define OBJECTS_HPP_

#include <exception/NullPointerException.hpp>
#include <string>

class Objects
{
	private:
		Objects();
		Objects(const Objects &other);

		virtual
		~Objects();

		Objects&
		operator=(const Objects &other);

	public:
		template<typename T>
			static T*
			requireNonNull(T *ptr)
			{
				if (ptr == NULL)
					throw NullPointerException();

				return (ptr);
			}

		template<typename T>
			static const T*
			requireNonNull(const T *ptr)
			{
				if (ptr == NULL)
					throw NullPointerException();

				return (ptr);
			}

		template<typename T>
			static T*
			requireNonNull(T *ptr, const char *message)
			{
				if (ptr == NULL)
					throw NullPointerException(message);

				return (ptr);
			}

		template<typename T>
			static const T*
			requireNonNull(const T *ptr, const char *message)
			{
				if (ptr == NULL)
					throw NullPointerException(message);

				return (ptr);
			}
};

#endif /* OBJECTS_HPP_ */
