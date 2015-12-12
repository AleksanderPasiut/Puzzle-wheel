#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class GRAPHICS
{
private:
	ID2D1Factory* d2d1_factory;
	IDWriteFactory* dwrite_factory;
	ID2D1HwndRenderTarget* target;
	IDWriteTextFormat* font;

	static const int brush_amount = 6;
	ID2D1SolidColorBrush* brush[brush_amount];

public:
	GRAPHICS(HWND);
	~GRAPHICS();

	ID2D1Factory*			Factory()		{ return d2d1_factory; }
	IDWriteFactory*			DWFactory()		{ return dwrite_factory; }
	ID2D1HwndRenderTarget*	Target()		{ return target; }
	IDWriteTextFormat*		Font()			{ return font; }
	ID2D1SolidColorBrush*	BrushBack()		{ return brush[0]; }
	ID2D1SolidColorBrush*	BrushText()		{ return brush[1]; }
	ID2D1SolidColorBrush*	BrushEdge()		{ return brush[2]; }
	ID2D1SolidColorBrush*	BrushCircle()	{ return brush[3]; }
	ID2D1SolidColorBrush*	BrushMarked()	{ return brush[4]; }
	ID2D1SolidColorBrush*	BrushBEdge()	{ return brush[5]; }
};