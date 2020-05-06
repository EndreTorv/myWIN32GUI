// myWIN32GUI.cpp : Defines the entry point for the application.
//
#define _DEBUG 1

#include "stdafx.h"
#include "myWIN32GUI.h"
#include <Windows.h>
#include "guicon.h"
#include <stdio.h>
#include "snake.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	#ifdef _DEBUG
		RedirectIOToConsole();
	#endif // !_DEBUG
	fprintf(stdout, "hey console \n");

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYWIN32GUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYWIN32GUI));
    MSG msg;

	//Initiate snake
	init_snake(&hWnd, 100, 100);
	

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = (WNDPROC)WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYWIN32GUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int red = 0;
	static int green = 0;
	static int blue = 125;
	static bool paint_flag = 0;
	if (red < 0 || red > 255)
		red = 0;
	if (green < 0 || green > 255)
		green = 0;
	static tile myTile(0, 0);
	static int timerID = 1;
	switch (message)
    {

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:

			// Process the LEFT ARROW key. 
			set_snake_direction(LEFT);
			fprintf(stdout, "button push:	LEFT\n");
			red -= 20;
			myTile.x -= 1;
			break;

		case VK_RIGHT:

			// Process the RIGHT ARROW key. 
			set_snake_direction(RIGHT);
			fprintf(stdout, "button push:	RIGHT\n");
			red += 20;
			myTile.x += 1;
			break;

		case VK_UP:

			// Process the UP ARROW key. 
			set_snake_direction(UP);
			fprintf(stdout, "button push:	UP\n");
			green += 20;
			myTile.y -= 1;
			break;

		case VK_DOWN:

			set_snake_direction(DOWN);
			// Process the DOWN ARROW key. 
			fprintf(stdout, "button push:	DOWN\n");
			green -= 20;
			myTile.y += 1;
			break;

		default:
			break;
		}
		//prolly remove !
		fprintf(stdout, "DIRECTION: %d\n", (int)get_snake_direction());
		//paint_flag = true;
		//paint(myTile, BLACK);
		/*if (UpdateWindow(hWnd))
		{
			fprintf(stdout, "UpdateWindow failed,	update region empty?\n");
		}*/
		
		//snake_step();
		break;


	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);


        break;
	case WM_TIMER:
		fprintf(stdout, "WM_TIMER\n");
		snake_step();
		break;
	case WM_CREATE:
		fprintf(stdout, "WM_CREATE\n");

		// Start the timer.  

		if (1 == SetTimer(hWnd, timerID, 100, (TIMERPROC)NULL)) {
			fprintf(stdout, "Setting timer WORKED\n");
		}

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
    case WM_DESTROY:
		KillTimer(hWnd, timerID);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
	fprintf(stdout, "msg: %d\n", message);
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
