/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pit.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:56:36 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:56:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIT_HPP_
# define PIT_HPP_

namespace kfs::pit
{
	void remap(int offset1, int offset2);
	void disable(void);
}

#endif /* PIT_HPP_ */
