/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:44:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/14 17:44:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP_
# define EASYFIND_HPP_

# include <algorithm>

template<typename T>
	bool
	easyfind(T &container, const int &n)
	{
		typename T::iterator iterator = std::find(container.begin(), container.end(), n);

		return (iterator != container.end());
	}

#endif /* EASYFIND_HPP_ */
