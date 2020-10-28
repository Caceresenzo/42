/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataUnit.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:07:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 15:07:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATAUNIT_HPP_
# define DATAUNIT_HPP_

#include <util/Enum.hpp>
#include <util/unit/DataSize.hpp>
#include <iostream>

class DataUnit :
		public Enum<DataUnit>
{
	public:
		typedef Enum<DataUnit>::iterator iterator;

	private:
		std::string m_suffix;
		DataSize m_size;

	public:
		DataUnit();
		DataUnit(const std::string &suffix, const DataSize &size);
		DataUnit(const DataUnit &other);

		virtual
		~DataUnit();

		DataUnit&
		operator=(const DataUnit &other);

		const std::string&
		suffix() const;

		const DataSize&
		size() const;

	public:
		static DataUnit *BYTES;
		static DataUnit *KILOBYTES;
		static DataUnit *MEGABYTES;
		static DataUnit *GIGABYTES;
		static DataUnit *TERABYTES;

	public:
		static DataUnit*
		fromSuffix(const std::string &suffix);
};

#endif /* DATAUNIT_HPP_ */
