#include "graphics.h"

GRAPHICS::GRAPHICS(HWND hwnd)
{
	// fabryka Direct2D
	if (S_OK != D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d1_factory))
		throw 0;

	try
	{
		// fabryka DirectWrite
		if (S_OK != DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&dwrite_factory)))
			throw 0;

		try
		{
			RECT rect;
			if (!GetClientRect(hwnd, &rect))
				throw 0;

			// RenderTarget okna
			if (S_OK != d2d1_factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
															 D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right-rect.left, rect.bottom-rect.top)),
															 &target))
				throw 0;

			try
			{
				// g³ówna czcionka
				if (S_OK != dwrite_factory->CreateTextFormat(L"Verdana",
															 0,
															 DWRITE_FONT_WEIGHT_NORMAL,
															 DWRITE_FONT_STYLE_NORMAL,
															 DWRITE_FONT_STRETCH_NORMAL,
															 0.07f,
															 L"pl_utf8",
															 &font))
					throw 0;

				font->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				font->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

				try
				{
					// pêdzle
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &brush[0]))
						throw brush_amount-1;
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.5f, 1.0f, 0.5f), &brush[1]))
						throw brush_amount-2;
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.2f, 0.6f, 0.2f), &brush[2]))
						throw brush_amount-3;
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.1f, 0.5f, 0.1f), &brush[3]))
						throw brush_amount-4;
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.2f, 0.8f, 0.2f), &brush[4]))
						throw brush_amount-5;
					if (S_OK != target->CreateSolidColorBrush(D2D1::ColorF(0.2f, 0.4f, 0.2f), &brush[5]))
						throw brush_amount-6;
				}
				catch(int failed_brush_amount) 
				{
					for (int i = 0; i < brush_amount-failed_brush_amount-1; i++)
						brush[i]->Release();
					font->Release();
					throw;
				}
			}
			catch (int) { target->Release(); throw; }
		}
		catch (int) { dwrite_factory->Release(); throw; }
	}
	catch (int) { d2d1_factory->Release(); throw; }
}
GRAPHICS::~GRAPHICS()
{
	for (int i = 0; i < brush_amount; i++)
		brush[i]->Release();
	font->Release();
	target->Release();
	dwrite_factory->Release();
	d2d1_factory->Release();
}