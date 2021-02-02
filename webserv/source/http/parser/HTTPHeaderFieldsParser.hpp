/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPHeaderFieldsParser.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:46:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/01 21:46:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPHEADERFIELDSPARSER_HPP_
# define HTTPHEADERFIELDSPARSER_HPP_

#include <http/header/HTTPHeaderFields.hpp>
#include <string>

class DataSize;

class HTTPHeaderFieldsParser
{
	public:
		enum State
		{
			S_FIELD,
			S_COLON,
			S_SPACES_BEFORE_VALUE,
			S_VALUE,
			S_SPACES_AFTER_VALUE,
			S_END_R,
			S_END_N,
			S_END_R2,
			S_END,
		};

	public:
		static DataSize MAX_SIZE;

	private:
		bool m_limited;
		State m_state;
		HTTPHeaderFields m_headerFields;
		std::string m_key;
		std::string m_value;
		long m_consumed;

	public:
		HTTPHeaderFieldsParser(bool limited = true);

		void
		consume(char c);

		void
		reset();

		inline State
		state() const
		{
			return (m_state);
		}

		inline const HTTPHeaderFields&
		headerFields() const
		{
			return (m_headerFields);
		}

	private:
		void
		commit(State nextState);
};

#endif /* HTTPHEADERFIELDSPARSER_HPP_ */
