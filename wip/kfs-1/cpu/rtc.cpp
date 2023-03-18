/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:49:26 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:49:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/io.hpp>
#include <cpu/rtc.hpp>
#include <stdio.h>
#include <string.h>

#define	CMOS_ADDRESS 0x70
#define	CMOS_DATA 0x71
#define	CURRENT_YEAR 2023

namespace kfs::rtc
{
	uint8_t read_register(uint8_t register_)
	{
		kfs::io::outb(CMOS_ADDRESS, register_);
		kfs::io::wait();

		return (kfs::io::inb(CMOS_DATA));
	}

	void wait_until_update_finished()
	{
		while (read_register(0x0A) & 0x80)
			1;
	}

	void do_read(rtc_time_t &time)
	{
		wait_until_update_finished();

		time.second = read_register(0x00);
		time.minute = read_register(0x02);
		time.hour = read_register(0x04);
		time.day = read_register(0x07);
		time.month = read_register(0x08);
		time.year = read_register(0x09);
	}

	rtc_time_t read()
	{
		rtc_time_t time;
		rtc_time_t last;

		do_read(time);
		do
		{
			last = time;
			do_read(time);
		}
		while (memcmp(&last, &time, sizeof(rtc_time_t)) == 0);

		uint8_t b_reg = read_register(0x0B);

		/* convert BCD to binary values if necessary */
		if (!(b_reg & 0x04))
		{
#define CONVERT(x) x = (((x) & 0x0F) + (((x) / 16) * 10))

			CONVERT(time.second);
			CONVERT(time.minute);
			CONVERT(time.hour);
			CONVERT(time.day);
			CONVERT(time.month);
			CONVERT(time.year);
		}

		/* convert 12 hour clock to 24 hour clock if necessary */
		if (!(b_reg & 0x02) && (time.hour & 0x80))
		{
			time.hour = ((time.hour & 0x7F) + 12) % 24;
		}

		/* calculate the full (4-digit) year */
		time.year += (CURRENT_YEAR / 100) * 100;
		if (time.year < CURRENT_YEAR)
			time.year += 100;

		return (time);
	}
}
