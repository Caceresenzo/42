/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonBase.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:36:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:36:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONBASE_HPP_
# define JSONBASE_HPP_

# include <string>

class JSONBase
{
	public:
		virtual
		~JSONBase();

		virtual JSONBase*
		clone() const = 0;

		virtual std::string
		toJsonString() const = 0;

		template<typename T>
			bool
			instanceOf() const
			{
				return (!!dynamic_cast<const T*>(this));
			}

};

#endif /* JSONBASE_HPP_ */
