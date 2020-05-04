/*
 * DebugLevel.h
 * Include to propagate debug levels
 *
 *  Copyright (C) 2016-2020  Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 *
 *  This file is part of Arduino-Utils https://github.com/ArminJo/Arduino-Utils.
 *
 *  Arduino-Utils is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#ifndef DEBUGLEVEL_H_
#define DEBUGLEVEL_H_

// Propagate debug level
#ifdef TRACE 			// Information you need to understand details of a function or if you hunt a bug.
#  ifndef DEBUG
#define DEBUG			// Information need to understand the operating of your program. E.g. function calls and values of control variables.
#  endif
#endif
#ifdef DEBUG
#  ifndef INFO
#define INFO 			// Information you want to see in regular operation to see what the program is doing. E.g. "START ../src/LightToTone.cpp Version 1.2 from Dec 31 2019" or "Now playing Muppets melody".
#  endif
#endif
#ifdef INFO
#  ifndef WARN
#define WARN			// Information that the program may encounter problems, like small Heap/Stack area.
#  endif
#endif
#ifdef WARN
#  ifndef ERROR
#define ERROR			// Informations to explain why the program will not run. E.g. not enough Ram for all created objects.
#  endif
#endif

#endif /* DEBUGLEVEL_H_ */

#pragma once
