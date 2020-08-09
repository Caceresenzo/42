/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OfficeBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:53:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 17:53:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OFFICEBLOCK_HPP_
# define OFFICEBLOCK_HPP_

# include "Bureaucrat.hpp"
# include "Intern.hpp"

class OfficeBlock
{
	private:
		Intern *_intern;
		Bureaucrat *_signer;
		Bureaucrat *_executor;

		OfficeBlock(const OfficeBlock &other);

		OfficeBlock& operator=(const OfficeBlock &other);

		void validateStaff();

	public:
		OfficeBlock();
		OfficeBlock(Intern &intern, Bureaucrat &signer, Bureaucrat &executor);

		virtual ~OfficeBlock();

		void doBureaucracy(const std::string formName, const std::string target);

		void setIntern(Intern &intern);
		void setExecutor(Bureaucrat &executor);
		void setSigner(Bureaucrat &signer);

		class IllegalStateException : public std::exception
		{
			private:
				const std::string _message;

			public:
				IllegalStateException(void);
				IllegalStateException(std::string message);
				IllegalStateException(const IllegalStateException &other);

				virtual ~IllegalStateException(void) throw ();

				IllegalStateException& operator=(const IllegalStateException &other);

				virtual const char* what() const throw ();

				const std::string &getMessage() const;
		};

		class UnsupportedOperationException : public std::exception
		{
			private:
				const std::string _message;

			public:
				UnsupportedOperationException(void);
				UnsupportedOperationException(std::string message);
				UnsupportedOperationException(const UnsupportedOperationException &other);

				virtual ~UnsupportedOperationException(void) throw ();

				UnsupportedOperationException& operator=(const UnsupportedOperationException &other);

				virtual const char* what() const throw ();

				const std::string &getMessage() const;
		};
};

#endif /* OFFICEBLOCK_HPP_ */
