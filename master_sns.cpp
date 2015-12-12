#include <WindowsX.h>

#include "master.h"

MASTER::SNS::SNS()
{
	transform = D2D1::IdentityMatrix();
}
void MASTER::SNS::Adjust(LPARAM lParam)
{
	float width = static_cast<float>(GET_X_LPARAM(lParam));
	float height = static_cast<float>(GET_Y_LPARAM(lParam));

	D2D1_POINT_2F translation;
	translation.x = width > height ? 0.5f*(width-height) : 0.0f;
	translation.y = height > width ? 0.5f*(height-width) : 0.0f;
	transform = D2D1::Matrix3x2F::Scale(min(width, height), min(width, height))*D2D1::Matrix3x2F::Translation(translation.x, translation.y);
	return;
}
D2D1_POINT_2F MASTER::SNS::Click(LPARAM lParam) const
{
	float x = static_cast<float>(GET_X_LPARAM(lParam));
	float y = static_cast<float>(GET_Y_LPARAM(lParam));

	float det = transform._11*transform._22-transform._12*transform._21;
	D2D1_POINT_2F ret;
	ret.x = (transform._22*(x-transform._31)-transform._12*(y-transform._32))/det;
	ret.y = (transform._11*(y-transform._32)-transform._21*(x-transform._31))/det;
	return ret;
}