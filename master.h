#pragma once

#include <Windows.h>

#include "graphics.h"
#include "puzzle.h"

class MASTER
{
private:
	HWND hwnd;
	GRAPHICS* graphics;
	PUZZLE* puzzle;
	
	struct SNS
	{
		D2D1_MATRIX_3X2_F transform;

		SNS();
		void Adjust(LPARAM);
		D2D1_POINT_2F Click(LPARAM) const;
	};
	SNS sns;

public:
	MASTER(HWND);
	~MASTER();

	void Paint() const;
	void Size(LPARAM);
	void Mouse(UINT, LPARAM);
};