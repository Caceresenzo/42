/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:54:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/01 11:54:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <climits>

const static char ALPHANUMERIC[] = "abcdefghijklmnopqrstuvwxyz0123456789";
const static size_t ALPHANUMERIC_SIZE = sizeof(ALPHANUMERIC) / sizeof(char);

struct Data
{
	std::string s1;
	int n;
	std::string s2;
};

void*
serialize(void)
{
	Data *ptr = new Data();

	ptr->s1.resize(9);
	ptr->s2.resize(9);

	for (int index = 0; index < 8; ++index)
	{
		ptr->s1 += ALPHANUMERIC[rand() % ALPHANUMERIC_SIZE];
		ptr->s2 += ALPHANUMERIC[rand() % ALPHANUMERIC_SIZE];
	}

	ptr->n = rand() % SHRT_MAX;

	return (ptr);
}

Data*
deserialize(void *raw)
{
	return (reinterpret_cast<Data*>(raw));
}

int
main(void)
{
	srand(time(NULL));

	void *raw = serialize();
	Data *data = deserialize(raw);

	std::cout << "s1: '" << data->s1 << "'" << std::endl;
	std::cout << " n:  " << data->n << std::endl;
	std::cout << "s2: '" << data->s2 << "'" << std::endl;

	delete data;

	return (EXIT_SUCCESS);
}
