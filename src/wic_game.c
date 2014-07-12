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
 * File:    wic_game.c
 * ----------------------------------------------------------------------------
 */
#include "wic_game.h"
enum WicError wic_init_game(WicGame* target, const char* title,
                            WicPair dimensions, unsigned int fps,
                            bool resizeable, bool fullscreen,
                            unsigned int samples)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(strcmp(title, "") == 0)
        return wic_report_error(WICER_TITLE);
    if(dimensions.x <= 1.0)
        return wic_report_error(WICER_DIMENSIONS_X);
    if(dimensions.y <= 1.0)
        return wic_report_error(WICER_DIMENSIONS_Y);
    if(fps == 0)
        return wic_report_error(WICER_FPS);
    if(!glfwInit())
        return wic_report_error(WICER_INIT_GLFW);
    glfwWindowHint(GLFW_REFRESH_RATE, fps);
    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_RESIZABLE, resizeable);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if(monitor == 0)
    {
        glfwTerminate();
        return wic_report_error(WICER_FETCH_MONITOR);
    }
    GLFWwindow* window;
    if(fullscreen)
        window = glfwCreateWindow(dimensions.x, dimensions.y, title, monitor,
                                  0);
    else
        window = glfwCreateWindow(dimensions.x, dimensions.y, title, 0, 0);
    if(window == 0)
    {
        glfwTerminate();
        return wic_report_error(WICER_CREATE_WINDOW);
    }
    glfwSetErrorCallback(wic_error_callback);
    glfwSetWindowFocusCallback(window, wic_focus_callback);
    glfwSetKeyCallback(window, wic_key_callback);
    glfwSetCharCallback(window, wic_char_callback);
    glfwSetCursorPosCallback(window, wic_cursor_location_callback);
    glfwSetScrollCallback(window, wic_scroll_callback);
    glfwMakeContextCurrent(window);
    glfwSetTime(0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    FT_Library freetype_library;
    int result = FT_Init_FreeType(&freetype_library);
    if(result != 0)
    {
        glfwTerminate();
        return wic_report_error(WICER_FREETYPE);
    }
    int physicalWidth; int physicalHeight;
    glfwGetMonitorPhysicalSize(monitor, &physicalWidth, &physicalHeight);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    WicPair device_resolution = {mode->width / (physicalWidth * 0.0393701),
                                 mode->height / (physicalHeight * 0.0393701)};
    
    target->p_window = window;
    target->p_dimensions = dimensions;
    target->seconds_per_frame = 1.0 / fps;
    target->p_previous_time = 0.0;
    target->delta = 0.0;
    target->p_freetype_library = freetype_library;
    target->p_device_resolution = device_resolution;
    return wic_report_error(WICER_NONE);
}
enum WicError wic_updt_game(WicGame* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    if(!glfwWindowShouldClose(target->p_window))
    {
        while(glfwGetTime() - target->p_previous_time <
              target->seconds_per_frame)
        {}
        wic_reset_input();
        glfwSwapBuffers(target->p_window);
        glFlush();
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        target->delta = glfwGetTime() - target->p_previous_time;
        target->p_previous_time = glfwGetTime();
        wic_report_error(WICER_NONE);
        glfwPollEvents();
        return 1;
    }
    return wic_report_error(WICER_NONE);
}
enum WicError wic_exit_game(WicGame* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    glfwSetWindowShouldClose(target->p_window, true);
    return wic_report_error(WICER_NONE);
}
enum WicError wic_free_game(WicGame* target)
{
    if(target == 0)
        return wic_report_error(WICER_TARGET);
    glfwDestroyWindow(target->p_window);
    target->p_window = 0;
    glfwTerminate();
    FT_Done_FreeType(target->p_freetype_library);
    
    target->p_window = 0;
    target->p_dimensions = (WicPair) {0,0};
    target->seconds_per_frame = 0.0;
    target->p_previous_time = 0.0;
    target->p_freetype_library = 0;
    target->p_device_resolution = (WicPair) {0,0};
    return wic_report_error(WICER_NONE);
}
static bool wic_focus = false;
static bool wic_down_keys[360] = {0};
static bool wic_pressed_keys[360] = {0};
static unsigned char wic_input[100] = {0};
static WicPair wic_cursor_location = {0.0,0.0};
static WicPair wic_scroll_offset = {0.0,0.0};
bool wic_is_key_down(enum WicKey key)
{
    return wic_down_keys[(int) key];
}
bool wic_is_key_pressed(enum WicKey key)
{
    return wic_pressed_keys[(int) key];
}
unsigned char* wic_get_input()
{
    return wic_input;
}
WicPair wic_get_cursor_location(WicGame* game)
{
    WicPair result = wic_cursor_location;
    result.y = game->p_dimensions.y - result.y;
    return result;
}
WicPair wic_get_scroll_offset()
{
    return wic_scroll_offset;
}
double wic_get_time()
{
    return glfwGetTime();
}
void wic_reset_input()
{
    memset(wic_pressed_keys, 0, sizeof(wic_down_keys));
    memset(wic_input, 0, sizeof(wic_input));
    wic_scroll_offset = (WicPair) {0,0};
}
void wic_error_callback(int error, const char* description)
{
    wic_report_error(WICER_GLFW);
}
void wic_focus_callback(GLFWwindow* window, int n)
{
    wic_focus = (bool) n;
}
void wic_key_callback(GLFWwindow* window, int key, int scancode, int action,
                      int mods)
{
    if(wic_focus && key < 360)
    {
        if(action == GLFW_RELEASE)
            wic_down_keys[key] = false;
        else if(action == GLFW_PRESS)
        {
            wic_down_keys[key] = true;
            wic_pressed_keys[key] = true;
        }
    }
}
void wic_char_callback(GLFWwindow* window, unsigned int key)
{
    if(wic_focus)
    {
        int startIndex = 0;
        while(startIndex < 100 && wic_input[startIndex] != 0)
            startIndex++;
        if(startIndex != 99)
            wic_input[startIndex] = (unsigned char) key;
    }
}
void wic_cursor_location_callback(GLFWwindow* window, double x, double y)
{
    if(wic_focus)
    {
        wic_cursor_location.x = x;
        wic_cursor_location.y = y;
    }
}
void wic_mouse_button_callback(GLFWwindow* window, int button, int action,
                               int mods)
{
    if(wic_focus)
    {
        if(action == GLFW_PRESS)
            wic_down_keys[button + 350] = true;
        else
            wic_down_keys[button + 350] = false;
    }
}
void wic_scroll_callback(GLFWwindow* window, double x, double y)
{
    if(wic_focus)
    {
        wic_scroll_offset.x = x;
        wic_scroll_offset.y = y;
    }
}
WicPair wic_convert_location(WicPair location, WicPair dimensions)
{
    WicPair result = wic_multiply_pairs(location, (WicPair) {2,2});
    result = wic_divide_pairs(result, dimensions);
    return wic_subtract_pairs(result, (WicPair) {1,1});
}