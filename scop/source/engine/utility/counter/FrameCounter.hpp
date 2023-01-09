/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FrameCounter.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:57:17 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/24 23:57:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAMECOUNTER_HPP_
# define FRAMECOUNTER_HPP_

class FrameCounter
{
	private:
		long long m_frame;
		long long m_last_time;
		long long m_last_per_seconds;

	public:
		FrameCounter();
		FrameCounter(const FrameCounter &other);

		virtual
		~FrameCounter();

		FrameCounter&
		operator=(const FrameCounter &other);

		void
		count();

		int
		frame() const;
};

#endif /* FRAMECOUNTER_HPP_ */
