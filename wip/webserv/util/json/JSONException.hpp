/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:05:45 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/23 17:05:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONEXCEPTION_HPP_
# define JSONEXCEPTION_HPP_

# include <exception/Exception.hpp>

class JSONException :
		public Exception
{
	private:
		std::string m_source;
		std::size_t m_index;

	public:
		JSONException(void);
		JSONException(const std::string &message, const std::string &source, std::size_t index);
		JSONException(const JSONException &other);

		virtual
		~JSONException() throw ();

		JSONException&
		operator=(const JSONException &other);

		const std::string&
		source() const;

		std::size_t
		index() const;
};

#endif /* JSONEXCEPTION_HPP_ */
