/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 16:37:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 16:37:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP_
# define ARRAY_TPP_

#include <exception>
#include <iostream>
#include <sstream>

template<typename T>
	class Array
	{
		private:
			unsigned int _size;
			T *_items;

		public:
			Array() : _size(0), _items(new T[0])
			{
			}

			Array(unsigned int n) : _size(n), _items(new T[n])
			{
			}

			Array(const Array &other) : _size(other._size), _items(NULL)
			{
				this->operator =(other);
			}

			virtual ~Array()
			{
				delete[] this->_items;
			}

			Array& operator=(const Array &other)
			{
				if (this != &other)
				{
					if (this->_items)
						this->~Array();

					this->_items = new T[this->_size = other._size];

					for (unsigned int index = 0; index < this->_size; ++index)
						this->_items[index] = other._items[index];
				}

				return (*this);
			}

			T& operator[](unsigned int index)
			{
				if (index < 0 || index >= _size)
					throw IndexOutOfBoundsException(index, _size);

				return this->_items[index];
			}

			unsigned int size() const
			{
				return (this->_size);
			}

			class IndexOutOfBoundsException : public std::exception
			{
				private:
					const std::string _message;

					std::string createMessage(int index, unsigned int size) {
						std::stringstream stream;

						stream << "index: " << index << ", size: " << size;

						return (stream.str());
					}

				public:
					IndexOutOfBoundsException(void) : _message("") {}

					IndexOutOfBoundsException(int index, size_t size) : _message(createMessage(index, size))
					{
					}

					IndexOutOfBoundsException(const IndexOutOfBoundsException &other) : _message("")
					{
						this->operator =(other);
					}

					virtual ~IndexOutOfBoundsException(void) throw ()
					{
					}

					IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException &other)
					{
						(void)other;

						return (*this);
					}

					virtual const char* what() const throw ()
					{
						return this->_message.c_str();
					}
			};
	};

#endif /* ARRAY_TPP_ */
