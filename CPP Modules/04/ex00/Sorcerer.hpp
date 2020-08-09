/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 12:18:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 12:18:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORCERER_HPP_
# define SORCERER_HPP_

# include <iostream>

# include "Victim.hpp"

class Sorcerer
{
	private:
		std::string _name;
		std::string _title;

		Sorcerer();

	public:
		Sorcerer(std::string name, std::string title);
		Sorcerer(const Sorcerer &other);

		virtual ~Sorcerer();

		Sorcerer& operator=(const Sorcerer &other);

		void polymorph(Victim const &) const;

		const std::string& getName() const;
		const std::string& getTitle() const;
};

std::ostream &operator <<(std::ostream &stream, Sorcerer &sorcerer);

#endif /* SORCERER_HPP_ */
