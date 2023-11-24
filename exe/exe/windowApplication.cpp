#include "windowApplication.h"
#include<cmath>

Window::Window(HINSTANCE& hIns):hInst(hIns)
{
	std::string cardioTextFile = "cardiology.txt";
	std::string surgTextFile = "surgical.txt";
	cardiology = new Cardiology(cardioTextFile);
	surgical = new Surgical(surgTextFile);
}

HWND& Window::createWindow(int xPos, int yPos, int width, int height, DWORD style)
{
	HWND window = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"DesktopApp",	L"База данных больницы", style,	xPos, yPos,	width, height, NULL, NULL, hInst, NULL);

	return window;
}

int Window::getCommand(HWND &hWnd, UINT uMsg, WPARAM &wParam, LPARAM &lParam)
{
	this->hWnd = hWnd;
	this->wParam = wParam;
	this->lParam = lParam;

	switch (uMsg)
	{
		case WM_CREATE:
		{
			//Просто полоски с подписями
			infoBar = CreateWindow(L"Static", L"Список пациентов кардиологического отделения", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, -1, 0, 750, 25, hWnd, (HMENU)id_static1, NULL, NULL);
			infoBar = CreateWindow(L"Static", L"Список пациентов хирургического отделения", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_CENTER, 748, 0, 750, 25, hWnd, (HMENU)id_static1, NULL, NULL);
			infoBar = CreateWindow(L"Static", L"№    номер карты\t      ФИО\t\t            пол\t\t    диагноз", WS_BORDER | WS_CHILD | WS_VISIBLE, -1, 25, 750, 25, hWnd, (HMENU)id_static1, NULL, NULL);
			infoBar = CreateWindow(L"Static", L"№    номер карты\t      ФИО\t\t            пол\t\t    диагноз", WS_BORDER | WS_CHILD | WS_VISIBLE, 748, 25, 750, 25, hWnd, (HMENU)id_static1, NULL, NULL);
			infoBar = CreateWindow(L"Static", L"№    номер карты\t      ФИО\t\t            пол", WS_BORDER | WS_CHILD | WS_VISIBLE, 525, 455, 450, 25, hWnd, (HMENU)id_static1, NULL, NULL);
			infoBar = CreateWindow(L"Static", L"Порядок ввода: номер карты, ФИО, пол, диагноз.", WS_BORDER | WS_CHILD | WS_VISIBLE, 375, 370, 750, 17, hWnd, (HMENU)id_static1, NULL, NULL);

			//Окна, выводящие результаты: кардиологическое отделение, хирургическое отделение, общее окно для отделений (для вывода всех пациентов и общих пациентов)
			listCardiology = CreateWindowA("Static", cardiology->print().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, -1, 50, 750, 320, hWnd, (HMENU)id_static1, hInst, NULL);
			listSurgical = CreateWindowA("Static", surgical->print().c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, 748, 50, 750, 320, hWnd, (HMENU)id_static1, NULL, NULL);
			resultWindow = CreateWindow(L"Static", L"", WS_BORDER | WS_CHILD | WS_VISIBLE, 525, 480, 450, 490, hWnd, (HMENU)id_static1, NULL, NULL);

			//Окно для ввода информации о новом пациенте
			addPatient = CreateWindow(L"Edit", L"", WS_BORDER | WS_CHILD | WS_VISIBLE, 375, 385, 750, 25, hWnd, (HMENU)id_edit1, NULL, NULL);

			//Кнопки
			button1 = CreateWindow(L"Button", L"Сортировка по имени", WS_BORDER | WS_CHILD | WS_VISIBLE, 15, 420, 200, 25, hWnd, (HMENU)id_button1, NULL, NULL);
			button2 = CreateWindow(L"Button", L"Сортировка по номеру", WS_BORDER | WS_CHILD | WS_VISIBLE, 265, 420, 200, 25, hWnd, (HMENU)id_button2, NULL, NULL);
			button3 = CreateWindow(L"Button", L"Фильтр по мужскому полу", WS_BORDER | WS_CHILD | WS_VISIBLE, 515, 420, 200, 25, hWnd, (HMENU)id_button3, NULL, NULL);
			button4 = CreateWindow(L"Button", L"Фильтр по женскому полу", WS_BORDER | WS_CHILD | WS_VISIBLE, 765, 420, 200, 25, hWnd, (HMENU)id_button4, NULL, NULL);
			button5 = CreateWindow(L"Button", L"Совпадающие пациенты", WS_BORDER | WS_CHILD | WS_VISIBLE, 1015, 420, 200, 25, hWnd, (HMENU)id_button5, NULL, NULL);
			button6 = CreateWindow(L"Button", L"Все пациенты", WS_BORDER | WS_CHILD | WS_VISIBLE, 1265, 420, 200, 25, hWnd, (HMENU)id_button6, NULL, NULL);
			button7 = CreateWindow(L"Button", L"Добавить пациента", WS_BORDER | WS_CHILD | WS_VISIBLE, 150, 385, 200, 25, hWnd, (HMENU)id_button7, NULL, NULL);
			button8 = CreateWindow(L"Button", L"Добавить пациента", WS_BORDER | WS_CHILD | WS_VISIBLE, 1150, 385, 200, 25, hWnd, (HMENU)id_button8, NULL, NULL);
		}
			break;
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == id_button1)
			{
				SetWindowTextA(listCardiology, cardiology->sortByName().c_str());
				SetWindowTextA(listSurgical, surgical->sortByName().c_str());
			}
			if (LOWORD(wParam) == id_button2)
			{
				SetWindowTextA(listCardiology, cardiology->sortByCardNumber().c_str());
				SetWindowTextA(listSurgical, surgical->sortByCardNumber().c_str());
			}
			if (LOWORD(wParam) == id_button3)
			{
				SetWindowTextA(listCardiology, cardiology->filterByGender("м").c_str());
				SetWindowTextA(listSurgical, surgical->filterByGender("м").c_str());
			}
			if (LOWORD(wParam) == id_button4)
			{
				SetWindowTextA(listCardiology, cardiology->filterByGender("ж").c_str());
				SetWindowTextA(listSurgical, surgical->filterByGender("ж").c_str());
			}
			if (LOWORD(wParam) == id_button5)
			{
				SetWindowTextA(resultWindow, cardiology->setIntersection(surgical).c_str());
			}
			if (LOWORD(wParam) == id_button6)
			{
				SetWindowTextA(resultWindow, cardiology->setUnion(surgical).c_str());
			}
			if (LOWORD(wParam) == id_button7)
			{
				char info[50];
				GetWindowTextA(addPatient, info, 50);
				cardiology->addPatient("cardiology.txt", info);
				SetWindowTextA(listCardiology, cardiology->print().c_str());
			}
			if (LOWORD(wParam) == id_button8)
			{
				char info[50];
				GetWindowTextA(addPatient, info, 50);
				surgical->addPatient("surgical.txt", info);
				SetWindowTextA(listSurgical, surgical->print().c_str());
			}
		}
			break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
			break;
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

Window::~Window()
{
	delete cardiology;
	delete surgical;
}
