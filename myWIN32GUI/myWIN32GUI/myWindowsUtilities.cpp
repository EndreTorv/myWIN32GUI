
#include "myWindowsUtilities.h"

int get_clientRect_relative_to_screen(HWND hWnd, LPRECT &recievingRect) {
	
	GetWindowRect(hWnd, recievingRect);
	//GetClientRect(hWnd, client_rect_ptr);
	//ClientToScreen(hWnd, client_rect_ptr);

	return 1;
}
