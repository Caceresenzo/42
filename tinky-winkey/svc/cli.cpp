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
Die(const char *message)
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

	std::cout << message << std::endl;
	std::cout << "Error " << errorMessageID << ": " << buffer;

	return (EXIT_FAILURE);
}

static int
Die(SC_HANDLE hService, const char *message)
{
	Die(message);

	if (hService)
		CloseServiceHandle(hService);

	return (EXIT_FAILURE);
}

static int
Success(const char *message)
{
	std::cout << message << std::endl;

	return (EXIT_SUCCESS);
}

static int
Success(SC_HANDLE hService, const char *message)
{
	Success(message);

	if (hService)
		CloseServiceHandle(hService);

	return (EXIT_SUCCESS);
}

static SC_HANDLE
Open(SC_HANDLE hSCManager, DWORD dwDesiredAccess)
{
	SC_HANDLE hService = OpenService(
		hSCManager,
		SERVICE_NAME,
		dwDesiredAccess);

	return (hService);
}

#define INSTALL_FAILURE "Service {tinky} could not be installed."
#define INSTALL_OK "Service {tinky} installed successfully."

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
		return (Die(hService, INSTALL_FAILURE));

	return (Success(hService, INSTALL_OK));
}

#define START_FAILURE "Service {tinky} could not be started."
#define START_OK "Service {tinky} started successfully."

static int
Start(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, SERVICE_START);
	if (!hService)
		return (Die(START_FAILURE));
	
	char argument[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, argument);

	const char *argumentVector[] = { argument };

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-startservicea */
	BOOL started = StartService(
		hService,
		1 /* NumServiceArgs */,
		argumentVector /* ServiceArgVectors */);

	if (!started)
		return (Die(hService, START_FAILURE));

	return (Success(hService, START_OK));
}

#define STOP_FAILURE "Service {tinky} could not be stopped."
#define STOP_OK "Service {tinky} stopped successfully."

static int
Stop(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, SERVICE_STOP);
	if (!hService)
		return (Die(STOP_FAILURE));

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-controlservice */
	SERVICE_STATUS serviceStatus = { 0 };
	BOOL stopped = ControlService(
		hService,
		SERVICE_CONTROL_STOP /* Control */,
		&serviceStatus /* ServiceStatus */);

	if (!stopped)
		return (Die(hService, STOP_FAILURE));

	return (Success(hService, STOP_OK));
}

#define DELETE_FAILURE "Service {tinky} could not be deleted."
#define DELETE_OK "Service {tinky} deleted successfully."

static int
Delete(SC_HANDLE hSCManager)
{
	SC_HANDLE hService = Open(hSCManager, SERVICE_QUERY_STATUS | SERVICE_STOP | DELETE);
	if (!hService)
		return (Die(DELETE_FAILURE));

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/ns-winsvc-service_status */
	SERVICE_STATUS serviceStatus = { 0 };
	bool queried = QueryServiceStatus(hService, &serviceStatus);
	if (queried && serviceStatus.dwCurrentState == SERVICE_RUNNING)
	{
		bool stopped = ControlService(
			hService,
			SERVICE_CONTROL_STOP /* Control */,
			&serviceStatus /* ServiceStatus */);

		if (stopped)
			Success(STOP_OK);
	}

	/* https://learn.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-deleteservice */
	bool deleted = DeleteService(hService);
	if (!deleted)
		return (Die(hService, DELETE_FAILURE));

	return (Success(hService, DELETE_OK));
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
		return (Die("Service controller could not be opened."));

	int code = Cli(program, argv[1], hSCManager);

	CloseServiceHandle(hSCManager);
	return (code);
}
