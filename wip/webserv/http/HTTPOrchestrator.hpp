/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPOrchestrator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 14:34:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 14:34:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPORCHESTRATOR_HPP_
# define HTTPORCHESTRATOR_HPP_

#include <config/Configuration.hpp>
#include <http/HTTPServer.hpp>
#include <vector>

class HTTPOrchestrator
{
	public:
		typedef std::vector<HTTPServer>::iterator iterator;

	private:
		Configuration m_configuration;
		std::vector<HTTPServer> m_servers;

		HTTPOrchestrator(const Configuration &configuration, const std::vector<HTTPServer> &servers);

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

	public:
		static HTTPOrchestrator
		create(const Configuration &configuration);
};

#endif
