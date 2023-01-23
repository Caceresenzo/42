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
#pragma warning(disable: 4820)

#include <Windows.h>
#include <winsvc.h>
#include <libloaderapi.h>
#include <winbase.h>
#include <TlHelp32.h>
#include <processthreadsapi.h>

#include <fstream>
#include <iostream>

#define SERVICE_NAME "tinky"

VOID WINAPI ServiceMain(DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler(DWORD);
int StartTheService();

#endif
