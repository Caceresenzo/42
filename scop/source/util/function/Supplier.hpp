/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Supplier.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 20:00:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/19 20:00:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPPLIER_HPP_
# define SUPPLIER_HPP_

template<typename T>
	class Supplier
	{
		protected:
			Supplier()
			{
			}

		public:
			virtual
			~Supplier()
			{
			}

		public:
			virtual T
			get() = 0;
	};

#endif /* SUPPLIER_HPP_ */
