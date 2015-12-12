#pragma once

#include <Windows.h>

#define CTRL_VOID 0x100
#define CTRL_OK 0x101
#define CTRL_EDIT 0x102

BOOL CALLBACK DialogInsertTextProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);