/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2014  Will O'Leary
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
 * File:    wic_error.c
 * ----------------------------------------------------------------------------
 */
#include "wic_error.h"
static enum WicError wic_error_code = WICER_NONE;
enum WicError wic_report_error(enum WicError code)
{
    wic_error_code = code;
    //if(code != WICER_NONE)
        //printf("%s%s", wic_translate_error_code(code), "\n");
    return code;
}
enum WicError wic_get_last_error()
{
    return wic_error_code;
}
const char* wic_translate_error_code(enum WicError code)
{
    switch(code)
    {
        /* general errors */
        case WICER_NONE:
            return "no error";
        case WICER_TARGET:
            return "target == null";
        case WICER_HEAP:
            return "out of heap memory";
        case WICER_GAME:
            return "game == null";
        case WICER_DIMENSIONS_X:
            return "dimension.x < 1";
        case WICER_DIMENSIONS_Y:
            return "dimension.y < 1";
        case WICER_FILEPATH:
            return "filepath == null";
        case WICER_FONT:
            return "font == null";
        case WICER_STRING:
            return "string == null";
            
        /* wic_game errors */
        case WICER_TITLE:
            return "empty title";
        case WICER_FPS:
            return "fps == 0";
        case WICER_INIT_GLFW:
            return "glfw3 could not be initialized";
        case WICER_FETCH_MONITOR:
            return "glfw3 monitor could not be fetched";
        case WICER_CREATE_WINDOW:
            return "window could not be created";
        case WICER_FREETYPE:
            return "freetype could not be initialized";
        case WICER_GLFW:
            return "glfw3 error";
        
        /* wic_color errors */
        case WICER_RED:
            return "red > 255";
        case WICER_GREEN:
            return "green > 255";
        case WICER_BLUE:
            return "blue > 255";
        case WICER_ALPHA:
            return "alpha > 255";
            
        /* wic_polygon errors */
        case WICER_NUM_VERTICES:
            return "num_vertices < 3";
        
        /* wic_texture errors */
        case WICER_BUFFER:
            return "buffer == null";
        case WICER_GPU:
            return "out of gpu memory";
        case WICER_FILE:
            return "file could not be found or loaded";
        
        /* wic_image errors */
        case WICER_TEXTURE:
            return "texture == null";
            
        /* wic_quad errors  */
            
        /* wic_font.h */
        case WICER_POINT:
            return "point == 0";

        /* wic_text.h */
            
        /* wic_server errors */
        case WICER_SOCKET:
            return "socket could not be reserved";
        case WICER_RESERVED_PORT:
            return "port < 1025, port reserved";
        case WICER_PORT_IN_USE:
            return "port in use";
        case WICER_ADDRESS_BIND:
            return "address could not be bound";
        case WICER_SERVER:
            return "server == 0";
        case WICER_PACKET:
            return "packet == 0";
        case WICER_CLIENT_DNE:
            return "client_id not assigned to any client";
        case WICER_RESULT:
            return "result == 0";
        case WICER_RESERVED_PACKET:
            return "packet uses reserved id (<= 4)";
        case WICER_BANNED_PACKET:
            return "packet from banned client";
        case WICER_REJECTED_CONNECT_PACKET:
            return "connection rejected (full server)";
        case WICER_NO_PACKET:
            return "no packet waiting to be recieved";
        case WICER_ADDRESS:
            return "address invalid";
        case WICER_ADDRESS_NULL:
            return "address == 0";
        case WICER_RESULT_LEN:
            return "result_len < 16";
            
        /* wic_client errors */
        case WICER_CLIENT:
            return "client == null";
        case WICER_TIMEOUT:
            return "function timed out";
        case WICER_PACKET_UNKNOWN_SOURCE:
            return "packet from unknown source";
        case WICER_NOT_JOINED:
            return "client not joined";
        case WICER_ALREADY_JOINED:
            return "client is already joined";

        default:
            return "unknown error";
    }
}
