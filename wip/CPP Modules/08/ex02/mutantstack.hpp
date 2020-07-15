/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutantstack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:40:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 14:40:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP_
# define MUTANTSTACK_HPP_

# include <queue>
# include <stack>

template<class T>
	class MutantStack : public std::stack<T>
	{
		public:
			typedef typename std::stack<T>::container_type::iterator iterator;

			MutantStack() : std::stack<T>()
			{
			}

			MutantStack(const MutantStack &other) : std::stack<T>(other)
			{
			}

			virtual ~MutantStack()
			{
			}

			MutantStack &operator=(const MutantStack &other)
			{
				std::stack<T>::operator =(other);
			}

			iterator begin()
			{
				return std::stack<T>::c.begin();
			}

			iterator end()
			{
				return std::stack<T>::c.end();
			}
	};

#endif /* MUTANTSTACK_HPP_ */
