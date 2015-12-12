#include <WindowsX.h>

#include "master.h"

#include "dialog_insert_text.h"

MASTER::MASTER(HWND hwnd)
{
	this->hwnd = hwnd;

	// grafika
	graphics = new GRAPHICS(hwnd);

	try
	{
		// uzyskanie podanego tekstu
		char* text = reinterpret_cast<char*>(DialogBox(0, "res_dialog_insert_text", hwnd, reinterpret_cast<DLGPROC>(DialogInsertTextProc)));

		// klasa puzzli
		puzzle = new PUZZLE(graphics, text);
	}
	catch(...) { delete graphics; }
}
MASTER::~MASTER()
{
	delete puzzle;
	delete graphics;
}

void MASTER::Paint() const
{
	ID2D1HwndRenderTarget& target = *(graphics->Target());
	target.BeginDraw();
	target.Clear(D2D1::ColorF(0));
	target.SetTransform(sns.transform);
	puzzle->Paint();
	target.EndDraw();
	return;
}
void MASTER::Size(LPARAM lParam)
{
	graphics->Target()->Resize(D2D1::SizeU(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
	sns.Adjust(lParam);
	Paint();
	return;
}
void MASTER::Mouse(UINT uMsg, LPARAM lParam)
{
	D2D1_POINT_2F click = sns.Click(lParam);
	puzzle->Mouse(uMsg, click);

	switch(uMsg)
	{
	case WM_LBUTTONDOWN: SetCapture(hwnd); break;
	case WM_LBUTTONUP: ReleaseCapture(); break;
	}

	Paint();
	return;
}
