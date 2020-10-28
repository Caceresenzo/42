/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataSize.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:37:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/28 11:37:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASIZE_HPP_
# define DATASIZE_HPP_

# include <iostream>

class DataUnit;

class DataSize
{
	public:
		static const long BYTES_PER_KB = 1024;
		static const long BYTES_PER_MB = BYTES_PER_KB * 1024;
		static const long BYTES_PER_GB = BYTES_PER_MB * 1024;
		static const long BYTES_PER_TB = BYTES_PER_GB * 1024;

	private:
		long long m_bytes;

	public:
		DataSize(void);
		DataSize(long long m_bytes);
		DataSize(const DataSize &other);

		virtual
		~DataSize();

		DataSize&
		operator=(const DataSize &other);

		long long
		toBytes() const;

	public:
		static DataSize
		ofBytes(long bytes);

		static DataSize
		ofKilobytes(long kilobytes);

		static DataSize
		ofMegabytes(long megabytes);

		static DataSize
		ofGigabytes(long gigabytes);

		static DataSize
		ofTerabytes(long terabytes);

		static DataSize
		of(long amount, const DataUnit &unit);

		static DataSize
		parse(const std::string &text);

		static DataSize
		parse(const std::string &text, const DataUnit &defaultUnit);
};

#include <util/unit/DataUnit.hpp>

#endif /* DATASIZE_HPP_ */
