#pragma once

#include<Windows.h>
#include"Cardiology.h"
#include"Surgical.h"

template <typename T> 
T clone(T object)
{
	return new T(object);
}

class Window
{
	Cardiology* cardiology;
	Surgical* surgical;

	HWND hWnd;
	LPARAM lParam;
	WPARAM wParam;
	HINSTANCE& hInst;


	HWND infoBar;

	HWND listSurgical;
	HWND listCardiology;
	HWND resultWindow;
	HWND addPatient;

	HWND button1;
	HWND button2;
	HWND button3;
	HWND button4;
	HWND button5;
	HWND button6;
	HWND button7;
	HWND button8;

	enum id
	{
		id_static1,

		id_button1,
		id_button2,
		id_button3,
		id_button4,
		id_button5,
		id_button6,
		id_button7,
		id_button8,
		
		id_edit1
	};
public:

	Window(HINSTANCE& hIns);
	HWND& createWindow(int xPos, int yPos, int width, int height, DWORD style);
	int getCommand(HWND &hwnd, UINT uMsg, WPARAM &wParam, LPARAM &lParam);

	~Window();
};
