/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OfficeBlock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:53:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 17:53:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OfficeBlock.hpp"

OfficeBlock::OfficeBlock() :
		_intern(NULL), _signer(NULL), _executor(NULL)
{
}

OfficeBlock::OfficeBlock(Intern &intern,
                         Bureaucrat &signer,
                         Bureaucrat &executor) :
		_intern(&intern), _signer(&signer), _executor(&executor)
{
}

OfficeBlock::~OfficeBlock()
{
}

OfficeBlock::OfficeBlock(const OfficeBlock &other) :
		_intern(NULL), _signer(NULL), _executor(NULL)
{
	(void)other;

	throw OfficeBlock::UnsupportedOperationException(
	        "copy constructor disabled");
}

OfficeBlock&
OfficeBlock::operator=(const OfficeBlock &other)
{
	(void)other;

	throw OfficeBlock::UnsupportedOperationException(
	        "= operator overload disabled");
}

void
OfficeBlock::validateStaff()
{
	if (!_intern)
		throw OfficeBlock::IllegalStateException("no intern provided");
	if (!_signer)
		throw OfficeBlock::IllegalStateException("no signer provided");
	if (!_executor)
		throw OfficeBlock::IllegalStateException("no executor provided");
}

void
OfficeBlock::doBureaucracy(const std::string formName, const std::string target)
{
	validateStaff();

	Form *form = _intern->makeForm(formName, target);

	if (form)
	{
		try
		{
			_signer->signForm(*form);
			_executor->executeForm(*form);
			
			delete form;
		}
		catch (std::exception &e)
		{
			delete form;

			throw;
		}
	}

}

void
OfficeBlock::setIntern(Intern &intern)
{
	this->_intern = &intern;
}

void
OfficeBlock::setSigner(Bureaucrat &signer)
{
	this->_signer = &signer;
}

void
OfficeBlock::setExecutor(Bureaucrat &executor)
{
	this->_executor = &executor;
}

OfficeBlock::IllegalStateException::IllegalStateException(void) :
		std::exception(), _message("no message")
{
}

OfficeBlock::IllegalStateException::IllegalStateException(
                                                          std::string message) :
		std::exception(), _message(message)
{
}

OfficeBlock::IllegalStateException::IllegalStateException(
        const IllegalStateException &other) :
		std::exception(), _message(other._message)
{
}

OfficeBlock::IllegalStateException::~IllegalStateException(void) throw ()
{
}

OfficeBlock::IllegalStateException&
OfficeBlock::IllegalStateException::operator =(
        const IllegalStateException &other)
{
	(void)other;

	return (*this);
}

const char*
OfficeBlock::IllegalStateException::what() const throw ()
{
	return (this->_message.c_str());
}

const std::string&
OfficeBlock::IllegalStateException::getMessage() const
{
	return (this->_message);
}

OfficeBlock::UnsupportedOperationException::UnsupportedOperationException(void) :
		std::exception(), _message("no message")
{
}

OfficeBlock::UnsupportedOperationException::UnsupportedOperationException(
        std::string message) :
		std::exception(), _message(message)
{
}

OfficeBlock::UnsupportedOperationException::UnsupportedOperationException(
        const UnsupportedOperationException &other) :
		std::exception(), _message(other._message)
{
}

OfficeBlock::UnsupportedOperationException::~UnsupportedOperationException(
        void) throw ()
{
}

OfficeBlock::UnsupportedOperationException&
OfficeBlock::UnsupportedOperationException::operator =(
        const UnsupportedOperationException &other)
{
	(void)other;

	return (*this);
}

const char*
OfficeBlock::UnsupportedOperationException::what() const throw ()
{
	return (this->_message.c_str());
}

const std::string&
OfficeBlock::UnsupportedOperationException::getMessage() const
{
	return (this->_message);
}

