/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:02:22 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 19:02:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URL_HPP_
# define URL_HPP_

#include <util/Optional.hpp>
#include <map>
#include <string>
#include <vector>

class URL
{
	public:
		class Builder;

	private:
		std::string m_path;
		Optional<std::map<std::string, std::string> > m_queryParameters;
		Optional<std::string> m_fragment;

	public:
		URL();
		URL(const std::string &path, const Optional<std::map<std::string, std::string> > queryParameters, const Optional<std::string> fragment);
		URL(const URL &other);

		virtual
		~URL();

		URL&
		operator =(const URL &other);

		const std::string&
		path() const;

		const Optional<std::map<std::string, std::string> >&
		queryParameters() const;

		const Optional<std::string>&
		fragment() const;

		std::string
		format(void) const;

		std::string
		queryString(void) const;

		bool
		filename(std::string &out) const;

		bool
		extension(std::string &out) const;

		Builder
		builder(void) const;

	public:
		static std::string
		encode(const std::string &input);

	public:
		class Builder
		{
			private:
				std::string m_path;
				Optional<std::map<std::string, std::string> > m_queryParameters;
				Optional<std::string> m_fragment;

			public:
				Builder();
				Builder(const URL &url);
				Builder(const Builder &other);

				virtual
				~Builder();

				Builder&
				operator =(const Builder &other);

				Builder&
				path(const std::string &path);

				Builder&
				appendToPath(const std::string &content);

				Builder&
				queryParameters(const std::map<std::string, std::string> &queryParameters);

				Builder&
				fragment(const std::string &fragment);

				URL
				build();
		};
};

#endif /* URL_HPP_ */
