/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_error.h
 * ----------------------------------------------------------------------------
 */
/** \file */
#ifndef WIC_ERROR_H
#define WIC_ERROR_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef enum
{
    WIC_ERRNO_NONE,
    WIC_ERRNO_ALREADY_INIT,
    WIC_ERRNO_NO_HEAP,
    WIC_ERRNO_LOAD_FILE_FAIL,
    WIC_ERRNO_NULL_TARGET,
    WIC_ERRNO_NULL_GAME,
    WIC_ERRNO_SMALL_X_DIMENSION,
    WIC_ERRNO_SMALL_Y_DIMENSION,
    WIC_ERRNO_NULL_TITLE,
    WIC_ERRNO_SMALL_TITLE,
    WIC_ERRNO_SMALL_FPS,
    WIC_ERRNO_GLFW_FAIL,
    WIC_ERRNO_MONITOR_FAIL,
    WIC_ERRNO_WINDOW_FAIL,
    WIC_ERRNO_FREETYPE_FAIL,
    WIC_ERRNO_NULL_BUFFER,
    WIC_ERRNO_NO_GPU_MEM,
    WIC_ERRNO_NULL_FILEPATH,
    WIC_ERRNO_NULL_TEXTURE,
    WIC_ERRNO_NULL_VERTICES,
    WIC_ERRNO_SMALL_NUM_VERTICES,
    WIC_ERRNO_SMALL_POINT,
    WIC_ERRNO_NULL_RESULT,
    WIC_ERRNO_NULL_FONT,
    WIC_ERRNO_NULL_STRING,
    WIC_ERRNO_INVALID_RED,
    WIC_ERRNO_INVALID_GREEN,
    WIC_ERRNO_INVALID_BLUE,
    WIC_ERRNO_INVALID_ALPHA,
    WIC_ERRNO_NULL_PACKET,
    WIC_ERRNO_NULL_NAME,
    WIC_ERRNO_SMALL_NAME,
    WIC_ERRNO_LARGE_NAME,
    WIC_ERRNO_RESERVED_PORT,
    WIC_ERRNO_NULL_SERVER_IP,
    WIC_ERRNO_SMALL_LEN_SERVER_IP,
    WIC_ERRNO_SOCKET_FAIL,
    WIC_ERRNO_PORT_IN_USE,
    WIC_ERRNO_SOCKET_BIND_FAIL,
    WIC_ERRNO_CLIENT_ALREADY_JOINED,
    WIC_ERRNO_JOIN_FAIL_FULL,
    WIC_ERRNO_JOIN_FAIL_BANNED,
    WIC_ERRNO_CLIENT_NOT_JOINED,
    WIC_ERRNO_TIMEOUT,
    WIC_ERRNO_PACKET_UNKNOWN_SOURCE,
    WIC_ERRNO_SMALL_MAX_CLIENTS,
    WIC_ERRNO_LARGE_MAX_CLIENTS,
    WIC_ERRNO_NOT_CLIENT_INDEX,
    WIC_ERRNO_IMPOSSIBLE_INDEX,
    WIC_ERRNO_INDEX_UNUSED,
    WIC_ERRNO_LARGE_REASON,
    WIC_ERRNO_NULL_NAME_OR_IP,
    WIC_ERRNO_LARGE_NAME_OR_IP,
    WIC_ERRNO_UNBANNED_NAME_OR_IP,
    WIC_ERRNO_NO_SUCH_CLIENT,
} WicError;
extern WicError wic_errno;
/** \brief translates the lastest wic_errno into a meaningful string and
 *  	   prints the string to stderr.
 */
void wic_print_errno_string();
/** \brief forces wic to print all thrown errors to stderr */
void wic_print_all_errors();
/** \brief forces pause at any errors */
void wic_pause_at_errors();
/** \brief throws an error
  *
  * \param error an error
  */
bool wic_throw_error(WicError error);
#endif

