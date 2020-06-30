/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 10:41:14 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 10:41:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>

#include "ShrubberyCreationForm.hpp"

static const char *SOME_TREE = ""
		"                                                         \n"
		"                      ,@@@@@@@,                          \n"
		"              ,,,.   ,@@@@@@/@@,  .oo8888o.              \n"
		"           ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o            \n"
		"          ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'         \n"
		"           %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'         \n"
		"          %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'           \n"
		"          `&%\\ ` /%&'    |.|        \\ '|8'             \n"
		"              |o|        | |         | |                 \n"
		"              |.|        | |         | |                 \n"
		"        jgs \\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_   \n"
		" -----------------------------------------------------   \n"
		"  https://asciiart.website/index.php?art=plants/trees    \n";

ShrubberyCreationForm::ShrubberyCreationForm() :
		Form()
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target) :
		Form("Shrubbery Creation", target, 145, 137)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) :
		Form(other)
{
	this->operator =(other);
}

ShrubberyCreationForm&
ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	Form::operator =(other);

	return (*this);
}

void
ShrubberyCreationForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	std::ofstream out;

	out.open((getTarget() + "_shrubbery").c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

	if (!out.is_open())
		throw ShrubberyCreationForm::IOException();

	out << SOME_TREE;

	out.close();
}

ShrubberyCreationForm::IOException::IOException(void) :
		std::exception(), _errno(errno)
{
	errno = 0;
}

ShrubberyCreationForm::IOException::IOException(int errorNo) :
		std::exception(), _errno(errorNo)
{
}

ShrubberyCreationForm::IOException::IOException(const IOException &other) :
		std::exception(), _errno(other._errno)
{
	this->operator =(other);
}

ShrubberyCreationForm::IOException::~IOException(void) throw ()
{
}

ShrubberyCreationForm::IOException&
ShrubberyCreationForm::IOException::operator =(const IOException &other)
{
	(void)other;

	return (*this);
}

const char*
ShrubberyCreationForm::IOException::what() const throw ()
{
	return (std::strerror(this->_errno));
}
