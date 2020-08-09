/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:48:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 15:48:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP_
# define INTERN_HPP_

# include "Form.hpp"

class Intern
{
	public:
		static const std::string FORM_NAMES[FORM_IMPL_COUNT];
		static Form *(*FORM_FACTORIES[FORM_IMPL_COUNT])(const std::string);

		Intern();
		Intern(const Intern &other);

		virtual ~Intern();

		Intern& operator=(const Intern &other);

		Form *makeForm(const std::string name, const std::string target) const;

		class FormNotFoundException : public std::exception
		{
			private:
				const std::string _message;

			public:
				FormNotFoundException(void);
				FormNotFoundException(const std::string formName);
				FormNotFoundException(const FormNotFoundException &other);

				virtual ~FormNotFoundException(void) throw ();

				FormNotFoundException& operator=(const FormNotFoundException &other);

				virtual const char* what() const throw ();
		};
};

#endif /* INTERN_HPP_ */
