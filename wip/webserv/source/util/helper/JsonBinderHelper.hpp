/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonBinderHelper.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 01:44:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/17 01:44:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONBINDERHELPER_HPP_
# define JSONBINDERHELPER_HPP_

#include <config/Configuration.hpp>
#include <config/exceptions/ConfigurationBindException.hpp>
#include <util/Convert.hpp>
#include <util/helper/DeleteHelper.hpp>
#include <json/JsonArray.hpp>
#include <json/JsonObject.hpp>
#include <util/Objects.hpp>
#include <iterator>
#include <list>
#include <map>
#include <string>

class JsonBinderHelper
{
	private:
		JsonBinderHelper();
		JsonBinderHelper(const JsonBinderHelper &other);

		virtual
		~JsonBinderHelper();

		JsonBinderHelper&
		operator=(const JsonBinderHelper &other);

	public:
		template<typename T, typename JT>
			static std::list<T const*>
			buildBlocks(const std::string &path, const JsonArray &jsonArray, T*
			(*builder)(const std::string&, const JT&))
			{
				std::list<const T*> blocks;

				try
				{
					int index = 0;
					for (JsonArray::const_iterator it = jsonArray.begin(); it != jsonArray.end(); it++)
					{
						std::string ipath = path + "[" + Convert::toString(index) + "]";
						const JT &jsonType = jsonCast<JT>(ipath, *it);

						blocks.push_back((*builder)(ipath, jsonType));

						index++;
					}
				}
				catch (...)
				{
					DeleteHelper::pointers<T>(blocks);

					throw;
				}

				return (blocks);
			}

		template<typename T, typename JT>
			static std::list<T const*>
			buildBlocks(const std::string &path, const JsonObject &jsonObject, T*
			(*builder)(const std::string&, const std::string&, const JT&))
			{
				std::list<const T*> blocks;

				try
				{
					for (JsonObject::const_iterator it = jsonObject.begin(); it != jsonObject.end(); it++)
					{
						const std::string &key = it->first;
						std::string ipath = path + KEY_DOT + key;
						const JT &jsonType = jsonCast<JT>(ipath, it->second);

						blocks.push_back((*builder)(ipath, key, jsonType));
					}
				}
				catch (...)
				{
					DeleteHelper::pointers<T>(blocks);

					throw;
				}

				return (blocks);
			}

		template<typename JT, typename T>
			static std::list<T>
			buildCollection(const std::string &path, const JsonArray &jsonArray)
			{
				std::list<T> items;

				int index = 0;
				for (JsonArray::const_iterator it = jsonArray.begin(); it != jsonArray.end(); it++)
				{
					std::string ipath = path + "[" + Convert::toString(index) + "]";
					const JT &jsonType = jsonCast<JT>(ipath, *it);

					T item = jsonType; /* Automatic type operator cast. */
					items.push_back(item);

					index++;
				}

				return (items);
			}

		template<typename JT, typename T>
			static std::map<std::string, T>
			buildSimpleMap(const std::string &path, const JsonObject &jsonObject)
			{
				std::map<std::string, T> items;

				for (JsonObject::const_iterator it = jsonObject.begin(); it != jsonObject.end(); it++)
				{
					const std::string &key = it->first;

					std::string ipath = path + KEY_DOT + key;
					const JT &jsonType = jsonCast<JT>(ipath, it->second);

					T item = jsonType; /* Automatic type operator cast. */
					items.insert(items.end(), std::make_pair<std::string, T>(key, item));
				}

				return (items);
			}

		template<typename T>
			static const T&
			jsonCast(const std::string &path, const JsonValue *jsonValue)
			{
				Objects::requireNonNull(jsonValue, "jsonValue == null");

				if (!jsonValue->instanceOf<T>())
					throw ConfigurationBindException::uncastable<T>(path, *jsonValue);

				return (*(jsonValue->cast<T>()));
			}
};

#endif /* JSONBINDERHELPER_HPP_ */
