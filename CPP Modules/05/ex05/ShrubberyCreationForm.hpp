/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 10:41:14 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 10:41:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP_
# define SHRUBBERYCREATIONFORM_HPP_

# include <exception>

# include "Form.hpp"

class ShrubberyCreationForm : public Form
{
	public:
		ShrubberyCreationForm();
		ShrubberyCreationForm(const std::string target);
		ShrubberyCreationForm(const ShrubberyCreationForm &other);

		virtual ~ShrubberyCreationForm();

		ShrubberyCreationForm& operator=(const ShrubberyCreationForm &other);

		virtual void execute(Bureaucrat const &executor) const;

		static Form *factory(const std::string target);

		class IOException : public std::exception
		{
			private:
				const int _errno;

			public:
				IOException(void);
				IOException(int errorNo);
				IOException(const IOException &other);

				virtual ~IOException(void) throw ();

				IOException& operator=(const IOException &other);

				virtual const char* what() const throw ();
		};
};

#endif /* SHRUBBERYCREATIONFORM_HPP_ */
