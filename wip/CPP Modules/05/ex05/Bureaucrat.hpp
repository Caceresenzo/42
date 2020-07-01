/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:22:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/29 10:22:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP_
# define BUREAUCRAT_HPP_

# include <string>
# include <iostream>
# include <exception>

class Form;

class Bureaucrat
{
	private:
		const std::string _name;
		int _grade;

		int ensureGradeRange(int grade);

	public:
		static const int GRADE_HIGHEST;
		static const int GRADE_LOWEST;

		Bureaucrat(void);
		Bureaucrat(const std::string name, int grade);
		Bureaucrat(const Bureaucrat &other);

		virtual ~Bureaucrat(void);

		Bureaucrat& operator=(const Bureaucrat &other);

		int promote();
		int demote();

		void signForm(Form &form);
		void executeForm(Form const &form);

		const std::string& getName() const;
		int getGrade() const;

		class GradeTooHighException : public std::exception
		{
			public:
				GradeTooHighException(void);
				GradeTooHighException(const GradeTooHighException &other);

				virtual ~GradeTooHighException(void) throw ();

				GradeTooHighException& operator=(const GradeTooHighException &other);

				virtual const char* what() const throw ();
		};

		class GradeTooLowException : public std::exception
		{
			public:
				GradeTooLowException(void);
				GradeTooLowException(const GradeTooLowException &other);

				virtual ~GradeTooLowException(void) throw ();

				GradeTooLowException& operator=(const GradeTooLowException &other);

				virtual const char* what() const throw ();
		};
};

std::ostream& operator<<(std::ostream& outStream, const Bureaucrat& bureaucrat);

#endif /* BUREAUCRAT_HPP_ */

#include "Form.hpp" // Include late dependency
