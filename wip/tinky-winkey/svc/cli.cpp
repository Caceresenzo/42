/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 01:13:21 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/08 01:13:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tinky.hpp"

static int
Die(const char *function, const char *action)
{
	DWORD errorMessageID = ::GetLastError();
	char buffer[512];

	FormatMessage(
	FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS /* Flags */,
	NULL /* Source */,
		errorMessageID /* MessageId */,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) /* LanguageId */,
		buffer /* Buffer */,
		sizeof(buffer) /* Size */,
		NULL /* Arguments */);

	std::cout << "ERROR: " << function << ": " << action << ": (" << errorMessageID << ") " << buffer;

	return (EXIT_FAILURE);
}

static int
Success(const char *function)
{
	std::cout << "SUCCESS: " << function << std::endl;
	return (EXIT_SUCCESS);
}

#define DIE(action) (Die(__FUNCTION__, action))
#define SUCCESS() (Success(__FUNCTION__))

static SC_HANDLE
Open(SC_HANDLE hSCManager, DWORD dwDesiredAccess)
{
	SC_HANDLE hService = OpenService(
		hSCManager,
		SERVICE_NAME,
		dwDesiredAccess);

	if (!hService)
		DIE("OpenService");

	return (hService);
}

static int
Install(SC_HANDLE hSCManager)
{
	char commandLine[MAX_PATH] = { 0 };
	GetModuleFileName(0, commandLine, MAX_PATH);

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicea */
	SC_HANDLE hService = CreateService(
		hSCManager,
		SERVICE_NAME,
		SERVICE_NAME /* DisplayName */,
		SERVICE_ALL_ACCESS /* DesiredAccess */,
		SERVICE_WIN32_OWN_PROCESS /* ServiceType */,
		SERVICE_DEMAND_START /* StartType */,
		SERVICE_ERROR_NORMAL /* ErrorControl */,
		commandLine,
		NULL /* LoadOrderGroup */,
		NULL /* TagId */,
		NULL /* Dependencies */,
		NULL /* ServiceStartName */,
		NULL /* Password */);

	if (!hService)
		return (DIE("CreateService"));

	CloseServiceHandle(hService);

	return (SUCCESS());
}

static int
Start(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, SERVICE_START);
	if (!hService)
		return (EXIT_FAILURE);
	
	char argument[MAX_PATH] = { 0 };
	GetFullPathName("winkey.exe", MAX_PATH, argument, 0);

	const char *argumentVector[] = { argument };

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-startservicea */
	BOOL started = StartService(
		hService,
		1 /* NumServiceArgs */,
		argumentVector /* ServiceArgVectors */);

	if (!started)
		return (DIE("StartService"));

	CloseServiceHandle(hService);

	return (SUCCESS());
}

static int
Stop(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, SERVICE_STOP);
	if (!hService)
		return (EXIT_FAILURE);

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-controlservice */
	SERVICE_STATUS serviceStatus = { 0 };
	BOOL started = ControlService(
		hService,
		SERVICE_CONTROL_STOP /* Control */,
		&serviceStatus /* ServiceStatus */);

	if (!started)
		return (DIE("ControlService"));

	CloseServiceHandle(hService);

	return (SUCCESS());
}

static int
Delete(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, DELETE);
	if (!hService)
		return (EXIT_FAILURE);

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-deleteservice */
	bool deleted = DeleteService(hService);
	if (!deleted)
		return (DIE("DeleteService"));

	CloseServiceHandle(hService);

	return (SUCCESS());
}

static int
Usage(const char *argv0)
{
	std::cout << argv0 << " [ install, start, stop, delete ]" << std::endl;
	return (EXIT_FAILURE);
}

int Cli(const char *program, const char *operation, SC_HANDLE hSCManager)
{
	if (strcmp(operation, "install") == 0)
		return (Install(hSCManager));

	if (strcmp(operation, "start") == 0)
		return (Start(hSCManager));

	if (strcmp(operation, "stop") == 0)
		return (Stop(hSCManager));

	if (strcmp(operation, "delete") == 0)
		return (Delete(hSCManager));

	return (Usage(program));
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		int code = StartTheService();
		if (code == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}

	const char *program = argv[0];
	if (argc != 2)
		return (Usage(program));

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-openscmanagera */
	SC_HANDLE hSCManager = OpenSCManager(
	NULL /* MachineName */,
	NULL /* DatabaseName */,
	SC_MANAGER_ALL_ACCESS /* DesiredAccess */);

	if (!hSCManager)
		return (DIE("OpenSCManager"));

	int code = Cli(program, argv[1], hSCManager);

	CloseServiceHandle(hSCManager);

	return (code);
}
