/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 12:18:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 12:18:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VICTIM_HPP_
# define VICTIM_HPP_

# include <iostream>

class Victim
{
	protected:
		std::string _name;

		Victim();

	public:
		Victim(std::string name);
		Victim(const Victim &other);

		virtual ~Victim();

		Victim& operator=(const Victim &other);

		virtual void getPolymorphed() const;

		const std::string& getName() const;
};

std::ostream &operator <<(std::ostream &stream, Victim &victim);

#endif /* VICTIM_HPP_ */
