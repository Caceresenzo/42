/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContactManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:52:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACTMANAGER_HPP
# define CONTACTMANAGER_HPP

# include <iostream>
# include <string>

# include "Phonebook.hpp"
# include "Contact.hpp"

class ContactManager
{
	private:
		Contact contacts[MAX_CONTACT];
		int	added;

	public:
		ContactManager();

		bool canAddMore(void);
		int size(void);
		bool isEmpty(void);
		bool add(Contact contact);
		void display(Contact contact);
		void listAll(void);
		void interactiveSearch(void);
};

#endif /* CONTACTMANAGER_HPP */
