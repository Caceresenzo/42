/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 12:04:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/29 12:04:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP_
# define FORM_HPP_

#include <exception>
#include <iostream>

class Bureaucrat;

# include "Bureaucrat.hpp" // Include late dependency

# define FORM_IMPL_COUNT 3

class Form
{
	private:
		const std::string _name;
		const std::string _target;
		bool _signed;
		const int _requiredGradeToSign;
		const int _requiredGradeToExecute;

		int ensureGradeRange(int grade, bool sign);

	public:
		Form();
		Form(const Form &other);
		Form(const std::string name, const std::string target, int requiredGradeToSign, int requiredGradeToExecute);

		virtual ~Form();

		Form& operator=(const Form &other);

		void beSigned(Bureaucrat &bureaucrat);

		virtual void execute(Bureaucrat const &executor) const = 0;

		const std::string& getName() const;
		const std::string& getTarget() const;
		int getRequiredGradeToExecute() const;
		int getRequiredGradeToSign() const;
		bool isSigned() const;

		class GradeTooHighException : public std::exception
		{
			private:
				bool _sign;

			public:
				GradeTooHighException(void);
				GradeTooHighException(bool sign);
				GradeTooHighException(const GradeTooHighException &other);

				virtual ~GradeTooHighException(void) throw ();

				GradeTooHighException& operator=(const GradeTooHighException &other);

				virtual const char* what() const throw ();
		};

		class GradeTooLowException : public std::exception
		{
			private:
				bool _sign;

			public:
				GradeTooLowException(void);
				GradeTooLowException(bool sign);
				GradeTooLowException(const GradeTooLowException &other);

				virtual ~GradeTooLowException(void) throw ();

				GradeTooLowException& operator=(const GradeTooLowException &other);

				virtual const char* what() const throw ();
		};

		class NotSignedException : public std::exception
		{
			public:
				NotSignedException(void);
				NotSignedException(const NotSignedException &other);

				virtual ~NotSignedException(void) throw ();

				NotSignedException& operator=(const NotSignedException &other);

				virtual const char* what() const throw ();
		};
};

std::ostream& operator<<(std::ostream& outStream, const Form& form);

#endif /* FORM_HPP_ */
