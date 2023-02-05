/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:03:52 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 20:03:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <types.h>

namespace kfs::timer
{
	void initialize(void);
	uint32_t tick_count();
}

#endif /* TIMER_HPP_ */
