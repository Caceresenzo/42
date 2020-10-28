/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Closable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:12:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/19 15:12:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSABLE_HPP_
# define CLOSABLE_HPP_

# include <exception/IOException.hpp>

class Closable
{

	public:
		virtual
		~Closable();

		virtual void
		close() throw (IOException) = 0;

};

#endif /* CLOSABLE_HPP_ */
