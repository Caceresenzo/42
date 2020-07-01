/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CentralBureaucracy.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:55:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/30 18:55:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CENTRALBUREAUCRACY_HPP_
# define CENTRALBUREAUCRACY_HPP_

# include "OfficeBlock.hpp"

# define OFFICE_BLOCK_TOTAL 20
# define TARGET_QUEUE_SIZE 100

class CentralBureaucracy
{
	private:
		OfficeBlock _officeBlocks[OFFICE_BLOCK_TOTAL];
		std::string _targets[TARGET_QUEUE_SIZE];

		void ensureNotLocked();

	public:
		CentralBureaucracy();
		CentralBureaucracy(const CentralBureaucracy &other);

		virtual ~CentralBureaucracy();

		CentralBureaucracy& operator=(const CentralBureaucracy &other);

		bool hire(Bureaucrat &bureaucrat);
		bool queueUp(std::string targetToQueue);

		int workableOffice();

		void doBureaucracy();
};

#endif /* CENTRALBUREAUCRACY_HPP_ */
