#pragma once
#include <math.h>
#define PI 3.141592

struct Vector2 // 점이다
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;


	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}

	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}

	Vector2(UINT32 x, UINT32 y)
		: x(x)
		, y(y)
	{

	}

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;

		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	Vector2 operator/(const float ratio) // 비율이라는 뜻
	{
		Vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}

	Vector2 operator*(const float ratio) // 비율이라는 뜻
	{
		Vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}


	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}


	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		return sqrtf(x * x + y * y); // 요곳이 바로 루트이다.
	}

	Vector2& Normalize()
	{
		float length = Length(); //방향성을 띄도록 결국 1로 만들어 주는 작업을 해준것이다.
		x /= length;
		y /= length;

		return *this;
	}
};

namespace ty::math
{
						//코샤인
	//float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
	//float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);

	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;   // 1라디안은 57.3돈가? 그정도임 즉 코사인과 사인 세타값을 구하기 위해서는 라디안의 개념을 사용해야하고
		vector.Normalize();						// Normalize는 결국 1, 1로 만들어 준것이고.

		float x = vector.x * cosf(radian) - vector.y * sinf(radian); // 이것이 바로 강사 선생님이 주신 삼각함수를 활용한 벡터의 회전이다. x좌표는 x코사인세타 - y사인세타
		float y = vector.x * sinf(radian) + vector.y * cosf(radian); // 
		//atan
		//atan();
		return Vector2(x, y);
	}

	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y; // 내적
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x; // 외적
	}
}