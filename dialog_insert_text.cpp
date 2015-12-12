#include "dialog_insert_text.h"

BOOL CALLBACK DialogInsertTextProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_ACTIVATE:
		{
			SetFocus(GetDlgItem(hwnd, CTRL_EDIT));
			return FALSE;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case CTRL_OK:
				{
					HWND item = GetDlgItem(hwnd, CTRL_EDIT);
					int length = GetWindowTextLength(item);

					if (length < 3 || length > 18)
					{
						MessageBox(hwnd, "D³ugoœæ podanego tekstu musi byæ z zakresu 3-18", "B³¹d", MB_OK);
						return FALSE;
					}

					static char buffer[31];
					GetDlgItemText(hwnd, CTRL_EDIT, buffer, 19);
					EndDialog(hwnd, reinterpret_cast<INT_PTR>(buffer));
					return TRUE;
				}
			}

			return FALSE;
		}
	}

	return FALSE;
}