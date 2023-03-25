/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:49:44 by ecaceres          #+#    #+#             */
/*   Updated: 2023/03/18 18:49:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_HPP_
# define SHELL_HPP_

namespace kfs::shell
{
	typedef struct
	{
			const char *name;
			void (*function)(void);
	} command_t;

	void do_ft();
	void do_tick();
	void do_time();
	void do_cpuid();
	void do_reboot();
	void do_shutdown();
	void do_multiboot();
	void do_halt();
	void do_exit();
	void do_trace();
	void do_stack();
	void do_pci();
	void do_help();

	void initialize();
}

#endif /* SHELL_HPP_ */
