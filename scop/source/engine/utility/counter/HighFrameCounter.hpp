/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HighFrameCounter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:57:17 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 23:57:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIGHFRAMECOUNTER_HPP_
# define HIGHFRAMECOUNTER_HPP_

class HighFrameCounter
{
	private:
		long long m_frame;
		long long m_last_time;
		long long m_last_per_seconds;
		long long m_last;
		long long m_current;

	public:
		HighFrameCounter();
		HighFrameCounter(const HighFrameCounter &other);

		virtual
		~HighFrameCounter();

		HighFrameCounter&
		operator=(const HighFrameCounter &other);

		void
		reset();

		void
		start();

		void
		end();

		double
		delta_time() const;

		void
		count();

		int
		frame() const;
};

#endif /* HIGHFRAMECOUNTER_HPP_ */
