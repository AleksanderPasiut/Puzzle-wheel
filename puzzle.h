#pragma once

#include "list.h"
#include "graphics.h"

class PUZZLE
{
private:
	CycleList<wchar_t> org_list;
	CycleList<wchar_t> mod_list;
	int list_size;
	GRAPHICS* graphics;
	float shift_angle;
	bool correct;

	struct MA
	{
		bool clicked;
		D2D1_POINT_2F pt;
		wchar_t* marked;

		MA() : clicked(false), marked(0) {}
	};
	MA ma;

private:
	static float CalcRotation(const D2D1_POINT_2F& start, const D2D1_POINT_2F& end, const D2D1_POINT_2F& pivot);
	static bool PointInEllipse(const D2D1_ELLIPSE&, const D2D1_POINT_2F&);
	D2D1_POINT_2F RetElemPos(int) const;
	D2D1_ELLIPSE RetElemEllipse(int) const;
	D2D1_RECT_F RetElemRect(int) const;

private:
	void SwapLetters();
	void Compare();

public:
	PUZZLE(GRAPHICS* graphics, char* text);

	void Paint();
	void Mouse(UINT, const D2D1_POINT_2F&);
};