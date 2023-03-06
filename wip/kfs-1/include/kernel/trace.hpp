/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 20:03:52 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 20:03:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_HPP_
# define TRACE_HPP_

# include <types.h>

namespace kfs::trace
{
	typedef struct
	{
			uint32_t start;
			uint32_t end;
			const char *name;
	} symbol_t;

	extern symbol_t symbols_table[];

	symbol_t get_symbol(void *frame);

	int backtrace(void **buffer, int size);
}

#endif /* TRACE_HPP_ */
