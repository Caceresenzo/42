/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 19:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <util/URL.hpp>

URL::URL() :
		m_path(),
		m_queryParameters(),
		m_fragment()
{
}

URL::URL(const std::string &path, const Optional<std::map<std::string, std::string> > queryParameters, const Optional<std::string> fragment) :
		m_path(path),
		m_queryParameters(queryParameters),
		m_fragment(fragment)
{
}

URL::URL(const URL &other) :
		m_path(other.m_path),
		m_queryParameters(other.m_queryParameters),
		m_fragment(other.m_fragment)
{
}

URL::~URL()
{
}

URL&
URL::operator =(const URL &other)
{
	if (this != &other)
	{
		m_path = other.m_path;
		m_queryParameters = other.m_queryParameters;
		m_fragment = other.m_fragment;
	}

	return (*this);
}

const std::string&
URL::path() const
{
	return (m_path);
}

const Optional<std::map<std::string, std::string> >&
URL::queryParameters() const
{
	return m_queryParameters;
}

const Optional<std::string>&
URL::fragment() const
{
	return (m_fragment);
}

std::string
URL::format(void) const
{
	std::string out(m_path);

	if (m_queryParameters.present())
		out += "?" + queryString();

	if (m_fragment.present())
		out += "#" + m_fragment.get();

	return (out);
}

std::string
URL::queryString(void) const
{
	std::string out;

	if (m_queryParameters.present())
	{
		typedef std::map<std::string, std::string> map;

		const map &queryParams = m_queryParameters.get();

		for (map::const_iterator it = queryParams.begin(); it != queryParams.end(); it++)
		{
			out += encode(it->first) + "=" + encode(it->second);
			out += "&";
		}
	}

	return (out);
}

bool
URL::filename(std::string &out) const
{
	if (m_path.empty())
		return (false);

	std::string::size_type lastSlashPos = m_path.rfind("/");

	if (lastSlashPos != std::string::npos)
		out = m_path.substr(lastSlashPos + 1);
	else
		out = m_path;

	return (true);
}

bool
URL::extension(std::string &out) const
{
	std::string filename;
	if (!URL::filename(filename))
		return (false);

	std::string::size_type lastDotPos = filename.rfind(".");

	if (lastDotPos == std::string::npos)
		return (false);

	out = filename.substr(lastDotPos + 1);

	return (true);
}

URL::Builder
URL::builder(void) const
{
	return (Builder(*this));
}

URL::Builder::Builder() :
		m_path(),
		m_queryParameters(),
		m_fragment()
{
}

URL::Builder::Builder(const URL &url) :
		m_path(url.m_path),
		m_queryParameters(url.m_queryParameters),
		m_fragment(url.m_fragment)
{
}

URL::Builder::Builder(const Builder &other) :
		m_path(other.m_path),
		m_queryParameters(other.m_queryParameters),
		m_fragment(other.m_fragment)
{
}

URL::Builder::~Builder()
{
}

URL::Builder&
URL::Builder::operator =(const Builder &other)
{
	if (this != &other)
	{
		m_path = other.m_path;
		m_queryParameters = other.m_queryParameters;
		m_fragment = other.m_fragment;
	}

	return (*this);
}

URL::Builder&
URL::Builder::path(const std::string &path)
{
	m_path = path;

	return (*this);
}

URL::Builder&
URL::Builder::appendToPath(const std::string &content)
{
	m_path += content;

	return (*this);
}

URL::Builder&
URL::Builder::queryParameters(const std::map<std::string, std::string> &queryParameters)
{
	m_queryParameters.set(queryParameters);

	return (*this);
}

URL::Builder&
URL::Builder::fragment(const std::string &fragment)
{
	m_fragment.set(fragment);

	return (*this);
}

URL
URL::Builder::build()
{
	return (URL(m_path, m_queryParameters, m_fragment));
}

std::string
URL::encode(const std::string &input)
{
	return (input);
}
