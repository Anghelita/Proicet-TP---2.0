#include <windows.h>
#include <CommCtrl.h>

#define IDI_ICON          101
#define IDR_MENU          102
#define IDM_FILE_NEW      999
#define IDM_FILE_EXIT     1000
#define IDM_ITEM          1001
#define ID_MDI_CLIENT     1002
#define IDC_CHILD_EDIT    1003
#define ID_MDI_FIRSTCHILD 1004


#define BUTTON1 1009
#define BUTTON2 1008

#define IMPUT1 2001
#define IMPUT2 2002

#define EXIT 3001
#define BROWSE 3002

#define ABOUT 4001
#define INSTRUCTIONS 4002

#define ELEMENTAR 5001
#define KMPT 5002
#define RK 5003
#define BM 5004

HWND hWndedit2;
HWND hWndedit1;
LPTSTR text = (LPTSTR)GlobalAlloc(GPTR, 10000000);
LPTSTR cuv = (LPTSTR)GlobalAlloc(GPTR, 100);


const char ClassName[] = "MainWindowClass";
const char ChildClassName[] = "ChildWindowClass";
HWND hWndClient;

LRESULT CALLBACK ChildProc(HWND    hWnd,
	UINT    Msg,
	WPARAM  wParam,
	LPARAM  lParam)
{

	switch (Msg)

	{

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case EXIT:
		{
			DestroyWindow(hWnd);
			PostQuitMessage(0);
		}
		break;

		case BUTTON1:
		{
			int len = GetWindowTextLength(GetDlgItem(hWnd, IMPUT1));
			if (len > 0)
			{
				int i;
				GetDlgItemText(hWnd, IMPUT1, text, len + 1);
			}
			if (strcmp(text, "Introduceti textul") == 0)
			{
				MessageBox(hWnd, "Introduceti textul!", "ATENTIE!", MB_OK |
					MB_ICONWARNING);
				break;
			}
			len = GetWindowTextLength(GetDlgItem(hWnd, IMPUT2));
			if (len > 0)
			{
				int i;
				GetDlgItemText(hWnd, IMPUT2, cuv, len + 1);
			}
			if (strcmp(cuv, "Introduceti cuvantul") == 0)
			{
				MessageBox(hWnd, "Introduceti cuvantul!", "ATENTIE!", MB_OK |
					MB_ICONWARNING);
				break;
			}
		}
		break;
		}
		break;
	}
	}

	return DefMDIChildProc(hWnd, Msg, wParam, lParam);
}


LRESULT CALLBACK WndProc(HWND    hWnd,
	UINT    Msg,
	WPARAM  wParam,
	LPARAM  lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
	{
		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 0);
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;


		hWndClient = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"MDICLIENT",
			NULL,
			WS_CHILD,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			hWnd,
			(HMENU)ID_MDI_CLIENT,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			(LPVOID)&ccs);

		if (!hWndClient)
		{
			MessageBox(hWnd, "Failed To Create The Client Window", "Error", MB_OK);
		}

		ShowWindow(hWndClient, SW_SHOW);
		HMENU hMenu, hSubMenu;
		hMenu = CreateMenu();
		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDR_MENU, "Menu");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
		hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDM_FILE_NEW, "&New");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Pseudocod algoritmi");
		SetMenu(hWnd, hMenu);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDM_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case IDM_FILE_NEW:
		{
			HWND hChild;
			CREATESTRUCT cs;
			ZeroMemory(&cs, sizeof(CREATESTRUCT));

			hChild = CreateWindowEx(
				WS_EX_MDICHILD,
				ChildClassName,
				"Child Window",
				WS_CHILD | WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				hWndClient,
				NULL,
				(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				&cs);
			HWND hWndtxt1 = CreateWindowEx(WS_EX_APPWINDOW,
				"STATIC",
				"Pasul 1:",
				WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | BS_DEFPUSHBUTTON,
				10,
				20,
				560,
				20,
				hChild,
				NULL,
				GetModuleHandle(NULL),
				NULL);

			hWndedit1 = CreateWindowEx(WS_EX_APPWINDOW,
				"EDIT",
				"Introduceti textul",
				WS_VSCROLL | WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | WS_BORDER | ES_MULTILINE,
				10,
				50,
				560,
				210,
				hChild,
				(HMENU)IMPUT1,
				GetModuleHandle(NULL),
				NULL);

			HWND hWndtxt2 = CreateWindowEx(WS_EX_APPWINDOW,
				"STATIC",
				"Pasul 2:",
				WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | BS_DEFPUSHBUTTON,
				10,
				280,
				560,
				20,
				hChild,
				NULL,
				GetModuleHandle(NULL),
				NULL);

			hWndedit2 = CreateWindowEx(WS_EX_APPWINDOW,
				"EDIT",
				"Introduceti cuvantul",
				WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | WS_BORDER | ES_MULTILINE,
				10,
				310,
				560,
				20,
				hChild,
				(HMENU)IMPUT2,
				GetModuleHandle(NULL),
				NULL);

			HWND hWndtxt3 = CreateWindowEx(WS_EX_APPWINDOW,
				"STATIC",
				"Pasul 3:",
				WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | BS_DEFPUSHBUTTON,
				10,
				350,
				560,
				20,
				hChild,
				NULL,
				GetModuleHandle(NULL),
				NULL);

			HWND hWndButton = CreateWindowEx(NULL,
				"BUTTON",//-stilul
				"COMPARA",//-ce srie pe el
				WS_TABSTOP | WS_VISIBLE |
				WS_CHILD | BS_DEFPUSHBUTTON,
				190,//-poz
				380,//-poz
				200,//-marime
				100,//-matime
				hChild,
				(HMENU)BUTTON1,
				GetModuleHandle(NULL),
				NULL);

			if (!hChild)
				MessageBox(hWnd, "Failed To Create The Child Window", "Error", MB_OK);
		}
		break;

		default:
		{
			if (LOWORD(wParam) >= ID_MDI_FIRSTCHILD)
				DefFrameProc(hWnd, hWndClient, Msg, wParam, lParam);
			else
			{
				HWND hChild;
				hChild = (HWND)SendMessage(hWndClient, WM_MDIGETACTIVE, 0, 0);
				if (hChild)
					SendMessage(hChild, WM_COMMAND, wParam, lParam);
			}
		}
		}
		return 0;
	}
	break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefFrameProc(hWnd, hWndClient, Msg, wParam, lParam);
	}
	return 0;
}


INT WINAPI WinMain(HINSTANCE  hInstance,
	HINSTANCE  hPrevInstance,
	LPSTR      lpCmdLine,
	INT        nCmdShow)
{


	WNDCLASSEX    wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName = ClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	wc.lpfnWndProc = (WNDPROC)ChildProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DSHADOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ChildClassName;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Failed To Register The Child Window Class", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	HWND    hWnd;

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		ClassName,
		"The title of my window",
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, "Window Creation Failed.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG    Msg;



	while (GetMessage(&Msg, NULL, 0, 0))

	{
		if (!TranslateMDISysAccel(hWndClient, &Msg))

		{

			TranslateMessage(&Msg);

			DispatchMessage(&Msg);

		}
	}
	return Msg.wParam;

}