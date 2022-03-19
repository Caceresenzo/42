/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReferenceCounter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:34:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/12 20:34:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFERENCECOUNTER_HPP_
# define REFERENCECOUNTER_HPP_

class ReferenceCounter
{
	private:
		long m_shared;
		long m_weak;

	public:
		ReferenceCounter();

	public:
		long
		get_shared() const;

		void
		add_shared();

		long
		release_shared();

		long
		get_weak() const;

		void
		add_weak();

		long
		release_weak();

		long
		get();
};

#endif /* REFERENCECOUNTER_HPP_ */
