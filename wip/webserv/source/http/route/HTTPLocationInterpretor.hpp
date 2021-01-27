/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPLocationInterpretor.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:11:25 by alicetetu         #+#    #+#             */
/*   Updated: 2021/01/22 11:42:47 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPLOCATIONINTERPRETOR_HPP_
# define HTTPLOCATIONINTERPRETOR_HPP_

#include <list>
#include <string>
#include <config/block/LocationBlock.hpp>

class HTTPLocationInterpretor
{
	public:
		enum State
		{
			S_NOT_STARTED,
			S_FIRST,
			S_START,
			S_EXACT_INTRO,
			S_EXACT,
			S_MIDDLE_START,
			S_MIDDLE,
			S_TILDE,
			S_SPACE_AFTER_TILDE,
			S_NO_CASE_MODIFIER,
			S_END,
			S_OVER,
		};
	
	private:
		State m_state;
		std::string m_path;
		std::string m_start;
		std::list<std::string> m_middleList;
		std::string m_middle;
		std::string m_end;;
		std::string m_exact;
		const LocationBlock *m_locationBlock;

		char m_firstChar;
		char m_lastChar;
		
	public:
		HTTPLocationInterpretor();
		HTTPLocationInterpretor(std::string path, const LocationBlock *locationBlock);
		HTTPLocationInterpretor(const HTTPLocationInterpretor &other);
		
		virtual
		~HTTPLocationInterpretor();

		HTTPLocationInterpretor&
		operator =(const HTTPLocationInterpretor &other);

		const std::string&
		start(void);

		const std::string&
		end(void);
		
		const std::string&
		exact(void);

		const char&
		firstChar(void);

		const char&
		lastChar(void);
		
		std::list<std::string>&
		middleList(void);

		void
		middleList(std::string &middleElement);

		std::string&
		middleElement(void);

		void
		erase();
		
		void
		setEnd(std::string end);
		
		bool
		next(char &c);

		void
		consume(char &c);

		void
		end(std::string &end);

		const LocationBlock *
		locationBlock();
};

#endif /* HTTPLocationInterpretor_HPP_ */

