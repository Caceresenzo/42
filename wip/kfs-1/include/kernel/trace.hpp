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

namespace kfs::trace
{
	int backtrace(void **buffer, int size);
}

#endif /* TRACE_HPP_ */
