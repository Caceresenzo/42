/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:56:36 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:56:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTC_HPP_
# define RTC_HPP_

#include <types.h>

namespace kfs::rtc
{
	typedef struct
	{
			uint8_t second;
			uint8_t minute;
			uint8_t hour;
			uint8_t day;
			uint8_t month;
			uint32_t year;
	} rtc_time_t;

	uint8_t read_register(uint8_t register_);
	void wait_until_update_finished();

	rtc_time_t read();
}

#endif /* RTC_HPP_ */
