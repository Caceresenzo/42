/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArrayList.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_HPP
# define ARRAYLIST_HPP

# include <string>

class Token;

class ArrayList
{
	private:
		std::size_t _capacity;
		std::size_t _size;
		Token **_array;

		Token *unsafeGet(std::size_t index) const;
		void ensureInternalCapacity(std::size_t of);
		void deleteArray(void);

	public:
		ArrayList(void);
		ArrayList(const ArrayList &other);
		ArrayList(const std::size_t initialCapacity);

		~ArrayList(void);

		ArrayList& operator =(const ArrayList &other);

		void add(Token *token);
		void push(Token *token);

		Token *remove(std::size_t index);

		Token *get(std::size_t index) const;
		Token *first(void) const;
		Token *peek(void) const;

		Token *pop(void);

		std::size_t indexOf(Token *token) const;

		std::size_t size(void) const;

		bool empty(void) const;

		Token **toArray(void) const;
};

#endif /* ARRAYLIST_HPP_ */
