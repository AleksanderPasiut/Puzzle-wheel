#include <cmath>

#include "puzzle.h"

float PUZZLE::CalcRotation(const D2D1_POINT_2F& start, const D2D1_POINT_2F& end, const D2D1_POINT_2F& pivot)
{
	float npx = end.x-pivot.x;  // punkt klikniêty
	float npy = end.y-pivot.y;
	float np = npx*npx+npy*npy;

	float opx = pivot.y-start.y;   // obracam "stary" punkt o 90 stopni przeciwnie 
	float opy = start.x-pivot.x;	// do ruchu wskazówek zegara
	float op = opx*opx+opy*opy;
				
	float on = (npx-opx)*(npx-opx)+(npy-opy)*(npy-opy);
	const float pi_d2 = 1.570796f;
	float dif = acos((op+np-on)/(2*sqrt(np*op)))-pi_d2;
	return dif;
}
bool PUZZLE::PointInEllipse(const D2D1_ELLIPSE& ellipse, const D2D1_POINT_2F& pt)
{
	const float a = min(ellipse.radiusX, ellipse.radiusY); // pó³oœ ma³a elipsy
	const float b = max(ellipse.radiusX, ellipse.radiusY); // pó³oœ wielka elipsy
	const float c = 2*b; // suma odleg³oœci od ognisk elipsy (sta³a elipsy)
	const float u = sqrt(b*b-a*a); // odleg³oœæ ogniska od œrodka elipsy
	const float c1 = ellipse.radiusX > ellipse.radiusY ? sqrt((ellipse.point.x-u-pt.x)*(ellipse.point.x-u-pt.x)+(ellipse.point.y-pt.y)*(ellipse.point.y-pt.y))
													   : sqrt((ellipse.point.y-u-pt.y)*(ellipse.point.y-u-pt.y)+(ellipse.point.x-pt.x)*(ellipse.point.x-pt.x));
	const float c2 = ellipse.radiusX > ellipse.radiusY ? sqrt((ellipse.point.x+u-pt.x)*(ellipse.point.x+u-pt.x)+(ellipse.point.y-pt.y)*(ellipse.point.y-pt.y))
													   : sqrt((ellipse.point.y+u-pt.y)*(ellipse.point.y+u-pt.y)+(ellipse.point.x-pt.x)*(ellipse.point.x-pt.x));
	if (c1+c2 <= c)
		return true;
	else return false;
}
D2D1_POINT_2F PUZZLE::RetElemPos(int i) const
{
	static const float t_pi = 6.28318f;
	static const float u_radius = 0.4f;

	return D2D1::Point2F(0.5f+u_radius*sin(shift_angle+t_pi*static_cast<float>(i)/static_cast<float>(list_size)),
						 0.5f+u_radius*cos(shift_angle+t_pi*static_cast<float>(i)/static_cast<float>(list_size)));
}
D2D1_ELLIPSE PUZZLE::RetElemEllipse(int i) const
{
	static const float u_radius = 0.07f;
	return D2D1::Ellipse(RetElemPos(i), u_radius, u_radius);
}
D2D1_RECT_F PUZZLE::RetElemRect(int i) const
{
	static const float a_shift = 0.04f;
	return D2D1::RectF(RetElemPos(i).x-a_shift,
					   RetElemPos(i).y-a_shift,
					   RetElemPos(i).x+a_shift,
					   RetElemPos(i).y+a_shift);
}

void PUZZLE::SwapLetters()
{
	try
	{
		wchar_t tmp = *mod_list.getCursor();
		*mod_list.getCursor() = *ma.marked;
	
		for (int i = 0; i < list_size; i++)
		{
			if (mod_list.getCursor() == ma.marked)
				*mod_list.getCursor() = tmp;
	
			mod_list.gotoNext();
		}
	}
	catch(...)
	{}

	return;
}
void PUZZLE::Compare()
{
	wchar_t* init_cursor = mod_list.getCursor();

	for (int i = 0; i < list_size; i++)
	{
		correct = true;
		for (int j = 0; j < list_size; j++)
		{
			if (*org_list.getCursor() != *mod_list.getCursor())
				correct = false;

			org_list.gotoNext();
			mod_list.gotoNext();
		}

		if (correct)
			return;

		org_list.gotoNext();
	}

	return;
}

PUZZLE::PUZZLE(GRAPHICS* graphics, char* text)
{
	try
	{
		srand(GetTickCount());

		// spisanie tekstu do list
		for (list_size = 0; text[list_size] != 0; list_size++)
		{	
			// oryginalna lista
			org_list.insert(static_cast<wchar_t>(text[list_size]));

			// lista modyfikowana
			mod_list.insert(static_cast<wchar_t>(text[list_size]));

			// losowe przesunięcie wskaźnika, aby pomieszać elementy
			rand()%2 ? mod_list.gotoNext() : mod_list.gotoPrior();
		}

		this->graphics = graphics;
		shift_angle = 0;
		correct = false;
	}
	catch(...) {}
}

void PUZZLE::Paint()
{
	for (int i = 0; i < list_size; i++)
		graphics->Target()->DrawLine(D2D1::Point2F(0.51f, 0.49f), RetElemPos(i), graphics->BrushBEdge(), 0.005f);

	for (int i = 0; i < list_size; i++)
	{	
		graphics->Target()->DrawLine(D2D1::Point2F(0.48f, 0.51f), RetElemPos(i), graphics->BrushEdge(), 0.005f);
		graphics->Target()->FillEllipse(RetElemEllipse(i), mod_list.getCursor() == ma.marked ? graphics->BrushMarked() : graphics->BrushCircle());
		graphics->Target()->DrawEllipse(RetElemEllipse(i), graphics->BrushEdge(), 0.005f);

		graphics->Target()->DrawRectangle(RetElemRect(i), graphics->BrushText(), 0.005f);
		graphics->Target()->DrawTextA(mod_list.getCursor(), 1, graphics->Font(), RetElemRect(i), graphics->BrushText());

		mod_list.gotoNext();
	}

	if (correct)
		graphics->Target()->DrawTextA(L"BA DUM TSS", 10, graphics->Font(), D2D1::RectF(0.0f, 0.0f, 1.0f, 1.0f), graphics->BrushText());

	return;
}
void PUZZLE::Mouse(UINT uMsg, const D2D1_POINT_2F& click)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			ma.clicked = true;
			for (int i = 0; i < list_size; i++)
			{
				if (PointInEllipse(RetElemEllipse(i), click))
				{
					ma.clicked = false;
					
					if (ma.marked)
					{
						SwapLetters();
						Compare();
						ma.marked = 0;
					}
					else ma.marked = mod_list.getCursor();
				}
				mod_list.gotoNext();
			}
			
			ma.pt = click;
			break;
		}
	case WM_MOUSEMOVE:
		{
			if (ma.clicked)
			{
				shift_angle += CalcRotation(ma.pt, click, D2D1::Point2F(0.5f, 0.5f));
				ma.pt = click;
			}
			break;
		}
	case WM_LBUTTONUP:
		{
			ma.clicked = false;
			break;
		}
	}
	return;
}