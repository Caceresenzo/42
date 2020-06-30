/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantPigTerminationForm.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:22:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 18:22:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTPIGTERMINATIONFORM_HPP_
# define MUTANTPIGTERMINATIONFORM_HPP_

# include "Form.hpp"

class MutantPigTerminationForm : public Form
{
	public:
		MutantPigTerminationForm();
		MutantPigTerminationForm(const std::string target);
		MutantPigTerminationForm(const MutantPigTerminationForm &other);

		virtual ~MutantPigTerminationForm();

		MutantPigTerminationForm& operator=(const MutantPigTerminationForm &other);

		virtual void execute(Bureaucrat const &executor) const;

		static Form *factory(const std::string target);
};

#endif /* MUTANTPIGTERMINATIONFORM_HPP_ */
