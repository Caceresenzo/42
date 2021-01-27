/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_platform.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 23:15:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/25 23:15:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DETECT_PLATFORM_H_
# define DETECT_PLATFORM_H_

#ifdef __linux__
# define IS_LINUX 1
# define PLATFORM_NAME "linux"
#elif __APPLE__
# define IS_MACOS 1
# define PLATFORM_NAME "apple"
#elif __CYGWIN__
# define IS_CYGWIN 1
# define PLATFORM_NAME "cygwin"
#else
# error Unknown PLATFORM
#endif

#if defined(IS_LINUX) or defined(IS_MACOS)
# define IS_UNIX 1
#endif

#ifdef IS_CYGWIN
# define IS_WINDOWS 1
#endif

#ifndef IS_LINUX
# define IS_LINUX 0
#endif

#ifndef IS_MACOS
# define IS_MACOS 0
#endif

#ifndef IS_CYGWIN
# define IS_CYGWIN 0
#endif

#ifndef IS_WINDOWS
# define IS_WINDOWS 0
#endif

#if IS_LINUX || IS_MACOS
# define IS_UNIX 1
#else
# define IS_UNIX 0
#endif

#endif /* DETECT_PLATFORM_H_ */
