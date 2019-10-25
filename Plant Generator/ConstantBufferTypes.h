#pragma once
#include<DirectXMath.h>

struct ConstantBufferTransform
{
	DirectX::XMMATRIX transform;
};
struct ConstantBufferColour
{
	struct
	{
		float r;
		float g;
		float b;
		float a;
	} face_colors[6];
};