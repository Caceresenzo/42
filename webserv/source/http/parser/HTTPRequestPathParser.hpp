/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequestPathParser.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 21:10:12 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/11 15:43:55 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPREQUESTPATHPARSER_HPP_
# define HTTPREQUESTPATHPARSER_HPP_

#include <util/Optional.hpp>
#include <map>
#include <string>

class DataSize;

class HTTPRequestPathParser
{
	public:
		typedef void
		(HTTPRequestPathParser::*HexStorer)(char);

		enum State
		{
			S_PATH,
			S_QUERY_STRING_KEY,
			S_QUERY_STRING_VALUE,
			S_FRAGMENT,
			S_HEX_START,
			S_HEX_END,
			S_END,
		};

	public:
		static DataSize MAX_LENGTH;

	private:
		State m_state;
		std::string m_path;
		std::string m_original;
		std::string m_queryKey;
		std::string m_queryValue;
		State m_hexBeforeState;
		HexStorer m_hexStorer;
		std::string m_hex;
		Optional<std::map<std::string, std::string> > m_query;
		Optional<std::string> m_fragment;
		long m_dot;
		long m_level;

	public:
		HTTPRequestPathParser();

		void
		consume(char c);

		void
		reset();

		inline State
		state() const
		{
			return (m_state);
		}

		inline const std::string&
		path() const
		{
			return (m_path);
		}

		inline const std::string&
		original() const
		{
			return (m_path);
		}

		const Optional<std::map<std::string, std::string> >&
		query() const
		{
			return (m_query);
		}

		const Optional<std::string>&
		fragment() const
		{
			return (m_fragment);
		}

	private:
		void
		commitHexToPath(char c);

		void
		commitHexToKey(char c);

		void
		commitHexToValue(char c);

		void
		commitHexToFragment(char c);

		void
		commitQueryKeyValue(State nextState);

		inline void
		hexStart(HexStorer hexStorer)
		{
			m_hexBeforeState = m_state;
			m_state = S_HEX_START;
			m_hexStorer = hexStorer;
		}
};

#endif /* HTTPREQUESTPATHPARSER_HPP_ */
