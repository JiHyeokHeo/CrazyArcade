#pragma once

struct Vector2 // 점이다
{
	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}
	Vector2(Vector2& other) // 복사 생성자
		: x(other.x)
		, y(other.y)
	{

	}
};

