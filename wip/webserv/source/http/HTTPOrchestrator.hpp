/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPOrchestrator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alicetetu <alicetetu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:34:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/10 10:55:26 by alicetetu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPORCHESTRATOR_HPP_
# define HTTPORCHESTRATOR_HPP_

#include <http/HTTPServer.hpp>
#include <list>

class Configuration;
class Environment;
class Logger;

class HTTPOrchestrator
{
	public:
		typedef std::list<HTTPServer*> server_container;
		typedef server_container::iterator server_iterator;

	public:
		static Logger &LOG;

	private:
		server_container m_servers;
		bool m_running;
		bool m_stopping;

	private:
		HTTPOrchestrator(void);
		HTTPOrchestrator(const server_container &servers);
		HTTPOrchestrator(const HTTPOrchestrator &other);

		HTTPOrchestrator&
		operator=(const HTTPOrchestrator &other);

	public:
		virtual
		~HTTPOrchestrator();

	private:
		void
		prepare(void);

		void
		unprepare(void);

	public:
		void
		start();

		void
		stop();

	public:
		static HTTPOrchestrator*
		create();

		bool
		running() const
		{
			return (m_running);
		}

		bool
		stopping() const
		{
			return (m_stopping);
		}
};

#endif
