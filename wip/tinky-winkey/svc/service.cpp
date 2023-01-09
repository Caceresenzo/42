/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:45:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/08 17:45:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tinky.hpp"

#pragma comment(lib, "advapi32.lib")

SERVICE_STATUS g_ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE g_ServiceStopEvent = INVALID_HANDLE_VALUE;

STARTUPINFO g_StartupInfo;
PROCESS_INFORMATION g_ProcessInformation;

HANDLE FindProcessHandleByName(const char *name)
{
	HANDLE hProcess = NULL;

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		return (NULL);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hSnapshot, &pe32))
	{
		CloseHandle(hSnapshot);
		return (NULL);
	}

	do
	{
		if (_stricmp(pe32.szExeFile, name) == 0)
		{
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
			break;
		}
	}
	while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);
	return (hProcess);
}

int StartTheService()
{
	SERVICE_TABLE_ENTRY ServiceTable[] =
		{
			{ (CHAR*)SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
			{ NULL, NULL }
		};

	if (StartServiceCtrlDispatcher(ServiceTable) == FALSE)
		return ((int)GetLastError());

	return (EXIT_SUCCESS);
}

VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
	g_StatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, ServiceCtrlHandler);
	if (g_StatusHandle == NULL)
		return;

	// Tell the service controller we are starting
	ZeroMemory(&g_ServiceStatus, sizeof(g_ServiceStatus));
	g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	g_ServiceStatus.dwControlsAccepted = 0;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;
	SetServiceStatus(g_StatusHandle, &g_ServiceStatus);

	HANDLE hWinlogon = FindProcessHandleByName("winlogon.exe");
	if (!hWinlogon)
	{
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwWin32ExitCode = GetLastError();
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
		return;
	}

	HANDLE hToken = NULL;

	/* https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-openprocesstoken */
	BOOL opened = OpenProcessToken(
		hWinlogon,
		TOKEN_ALL_ACCESS /* DesiredAccess */,
		&hToken /* TokenHandle */);

	if (!opened)
	{
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwWin32ExitCode = GetLastError();
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
		return;
	}

	HANDLE hDuplicatedToken = NULL;

	/* https://learn.microsoft.com/en-us/windows/win32/api/securitybaseapi/nf-securitybaseapi-duplicatetokenex */
	BOOL duplicated = DuplicateTokenEx(
		hToken,
		TOKEN_ALL_ACCESS /* DesiredAccess */,
		NULL /* TokenAttributes */,
		SecurityImpersonation /* ImpersonationLevel */,
		TokenPrimary /* TokenType */,
		&hDuplicatedToken /* NewToken */);

	if (!duplicated)
	{
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwWin32ExitCode = GetLastError();
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
		return;
	}

	ZeroMemory(&g_StartupInfo, sizeof(g_StartupInfo));
	ZeroMemory(&g_ProcessInformation, sizeof(g_ProcessInformation));

	g_StartupInfo.cb = sizeof(g_StartupInfo);

	CHAR commandLine[] = "C:\\Windows\\System32\\notepad.exe";
	BOOL created = CreateProcessAsUser(
		hDuplicatedToken,
		NULL /* ApplicationName */,
		commandLine /* CommandLine */,
		NULL /* ProcessAttributes */,
		NULL /* ThreadAttributes */,
		FALSE /* InheritHandles */,
		CREATE_NO_WINDOW /* CreationFlags */,
		NULL /* Environment */,
		NULL /* CurrentDirectory */,
		&g_StartupInfo /* StartupInfo */,
		&g_ProcessInformation /* ProcessInformation */);

	if (!created)
	{
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwWin32ExitCode = GetLastError();
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
		return;
	}

	/* status update */
	{
		g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
	}

	WaitForSingleObject(g_ProcessInformation.hProcess, INFINITE);

	/* status update */
	{
		g_ServiceStatus.dwControlsAccepted = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
		g_ServiceStatus.dwCheckPoint = 2;
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
	}

	CloseHandle(g_ProcessInformation.hProcess);
	CloseHandle(g_ProcessInformation.hThread);
	CloseHandle(hToken);
	CloseHandle(hDuplicatedToken);

	/* status update */
	{
		g_ServiceStatus.dwControlsAccepted = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(g_StatusHandle, &g_ServiceStatus);
	}

	(void)argc;
	(void)argv;
}

VOID WINAPI ServiceCtrlHandler(DWORD CtrlCode)
{
	switch (CtrlCode)
	{
		case SERVICE_CONTROL_STOP:
		{
			if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
				break;

			g_ServiceStatus.dwControlsAccepted = 0;
			g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			g_ServiceStatus.dwCheckPoint = 1;

			TerminateProcess(g_ProcessInformation.hProcess, 3 /* SIGINT */);
			break;
		}
	}
}
