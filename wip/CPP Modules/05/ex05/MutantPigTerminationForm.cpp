/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantPigTerminationForm.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:22:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 18:22:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantPigTerminationForm.hpp"

MutantPigTerminationForm::MutantPigTerminationForm() :
		Form()
{
}

MutantPigTerminationForm::MutantPigTerminationForm(const std::string target) :
		Form("Mutant Pig Termination Form", target, 130, 50)
{
}

MutantPigTerminationForm::~MutantPigTerminationForm()
{
}

MutantPigTerminationForm::MutantPigTerminationForm(
        const MutantPigTerminationForm &other) :
		Form(other)
{
	this->operator =(other);
}

MutantPigTerminationForm&
MutantPigTerminationForm::operator=(const MutantPigTerminationForm &other)
{
	(void)other;

	return (*this);
}

void
MutantPigTerminationForm::execute(const Bureaucrat &executor) const
{
	Form::execute(executor);

	std::cout << "That'll do, Pigley. That'll do ..." << std::endl;
}

Form*
MutantPigTerminationForm::factory(const std::string target)
{
	return new MutantPigTerminationForm(target);
}
