// ----------------------------------------------------------------------------
// The Wick Engine - A simple, 2D, cross platform game library written in C++.
// Copyright (C) 2013-2014  Will O'Leary
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
// File:    WWindow.cpp
// ----------------------------------------------------------------------------

#include "WWindow.h"
namespace wick
{
	Window::Window(string title, Pair dimensions, State* state)
	{
        title_ = title;
        dimensions_ = dimensions;
		state_ = state;
	}
	int Window::start()
	{
        print("Wick Engine version " + wickVersion_ + " Copyright (C) 2013-2014  Will O'Leary\n");
		ApplicationHandle = this;
		hInstance_ = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.lpfnWndProc = WndProc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.hInstance = hInstance_;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "wickapp";

		RegisterClassEx(&wc);

		hWnd_ = CreateWindowEx(WS_EX_WINDOWEDGE, "wickapp", title_.c_str(), WS_OVERLAPPED | WS_CAPTION |
							   WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 0, 0,  dimensions_.x_ + 7,
							   dimensions_.y_ + 32, NULL, NULL, hInstance_, NULL);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
			| PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0,
			PFD_MAIN_PLANE, 0, 0, 0, 0
		};
		hdc_ = GetDC(hWnd_);
		int pixelFormat = ChoosePixelFormat(hdc_, &pfd);
		if(pixelFormat == 0)
            throwError(W_WWINDOW, "Unable to find compatible pixel format");
		SetPixelFormat(hdc_, pixelFormat, &pfd);
		hglrc_ = wglCreateContext(hdc_);
		wglMakeCurrent(hdc_, hglrc_);

		ShowWindow(hWnd_, SW_SHOW);

		const int UPDATE_TIMER_ID = 0;
		SetTimer(hWnd_, UPDATE_TIMER_ID , 15, NULL);
		const int SECOND_TIMER_ID = 1;
		SetTimer(hWnd_, SECOND_TIMER_ID, 1000, NULL);

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

        state_->initialize();
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}

	LRESULT Window::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		string key;
		switch(message)
		{
        case WM_TIMER:
            state_ -> update(this);
            glFlush();
            glClearColor(0.0,0.0,0.0,1.0);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            state_ -> paint(this);
            SwapBuffers(hdc_);
            return(0);
		case WM_DESTROY:
			delete(state_);
			wglMakeCurrent(hdc_, NULL);
			wglDeleteContext(hglrc_);
			PostQuitMessage(0);
			print("\nTerminated");
			return(0);
		case WM_MOUSEMOVE:
            POINT point;
			GetCursorPos(&point);
			if(ScreenToClient(hWnd, &point))
            {
                cursorLocation_.x_ = point.x;
                cursorLocation_.y_ = point.y;
            }
			return(0);
		case WM_KEYDOWN:
		    key = getWickName(wParam, lParam);
			downKeys_.push_back(key);
			pressedKeys_.push_back(key);
			return(0);
		case WM_KEYUP:
			key = getWickName(wParam, lParam);
			keyUp(key);
			return(0);
		case WM_LBUTTONDOWN:
			key = "LMB";
			downKeys_.push_back(key);
			pressedKeys_.push_back(key);
			return(0);
		case WM_LBUTTONUP:
			key = "LMB";
			keyUp(key);
			return(0);
		case WM_RBUTTONDOWN:
			key = "RMB";
			downKeys_.push_back(key);
			pressedKeys_.push_back(key);
			return(0);
		case WM_RBUTTONUP:
			key = "RMB";
			keyUp(key);
			return(0);
		case WM_MOUSEWHEEL:
			if((short) HIWORD(wParam)>0)
			{
				key = "MWF";
			}
			else
			{
				key = "MWB";
			}
			pressedKeys_.push_back(key);
			return(0);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	Pair Window::getDimensions()
	{
	    return(dimensions_);
	}
	Pair Window::getCursorLocation()
	{
	    return(cursorLocation_);
	}
	string Window::getWickName(WPARAM wParam, LPARAM lParam)
	{
	    string name = "";
	    switch(wParam)
		{
		case VK_BACK:
			name = "BACK";
		case VK_TAB:
			name = "TAB";
		case VK_CLEAR:
			name = "CLEAR";
		case VK_RETURN:
			name = "ENTER";
		case VK_SHIFT:
			name = "SHIFT";
		case VK_CONTROL:
			name = "CTRL";
		case VK_MENU:
			name = "ALT";
		case VK_CAPITAL:
			name = "CAPS";
		case VK_ESCAPE:
			name = "ESC";
		case VK_PRIOR:
			name = "PGUP";
		case VK_NEXT:
			name = "PGDOWN";
		case VK_END:
			name = "END";
		case VK_HOME:
			name = "HOME";
		case VK_LEFT:
			name = "LEFT";
		case VK_UP:
 			name = "UP";
		case VK_RIGHT:
			name = "RIGHT";
		case VK_DOWN:
			name = "DOWN";
		case VK_SNAPSHOT:
			name = "PRTSCREEN";
		case VK_INSERT:
			name = "INS";
		case VK_DELETE:
			name = "DEL";
		case VK_LWIN:
			name = "LWIN";
		case VK_RWIN:
			name = "RWIN";
		case VK_NUMLOCK:
			name = "NUM";
		case VK_SCROLL:
			name = "SCROLL";
		case VK_F1:
			name = "F1";
		case VK_F2:
			name = "F2";
		case VK_F3:
			name = "F3";
		case VK_F4:
			name = "F4";
		case VK_F5:
			name = "F5";
		case VK_F6:
			name = "F6";
		case VK_F7:
			name = "F7";
		case VK_F8:
			name = "F8";
		case VK_F9:
			name = "F9";
		case VK_F10:
			name = "F10";
		case VK_F11:
			name = "F11";
		case VK_F12:
			name = "F12";
		default:
			BYTE state[256];
            GetKeyboardState(state);
            wchar_t temp2[2];
            int result = ToUnicode(wParam,(lParam >> 16) & 0xFF, state, temp2, 2, 1);
            if(result > 0)
            {
                std::wstring wstr = (std::wstring) temp2;
                string strTo(1,0);
                WideCharToMultiByte (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], 1, NULL, NULL);
                name = strTo;
            }
		}
		return(name);
	}
	void Window::keyUp(string key)
	{
	    unsigned int len = downKeys_.size();
        for(unsigned int i = 0; i < len; i++)
        {
            if(downKeys_[i] == key)
            {
                downKeys_.erase(downKeys_.begin() + i);
                len--;
                i--;
            }
        }
	}
	bool Window::keyDown(string key)
	{
        unsigned int len = downKeys_.size();
        for(unsigned int i = 0; i < len; i++)
		{
			if(downKeys_[i] == key)
			{
				return(true);
			}
		}
		return(false);
	}
	vector<string> Window::getDownKeys()
	{
        return(downKeys_);
	}
	bool Window::keyPressed(string key)
	{
        unsigned int len = pressedKeys_.size();
        for(unsigned int i = 0; i < len; i++)
		{
			if(pressedKeys_[i] == key)
			{
				return(true);
			}
		}
		return(false);
	}
	vector<string> Window::getPressedKeys()
	{
	    return(pressedKeys_);
	}
    long double Window::time()
	{
        return((long double) clock()/CLOCKS_PER_SEC);
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return(ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam));
	}
}
