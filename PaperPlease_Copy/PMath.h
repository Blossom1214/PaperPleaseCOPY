#pragma once
#include <cmath>
#include <algorithm>

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2() = default;
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	/// 벡터 덧셈
	Vector2 operator+(const Vector2& other) const { return { x + other.x, y + other.y }; }
	/// 벡터 뺄셈
	Vector2 operator-(const Vector2& other) const { return { x - other.x, y - other.y }; }
	/// 스칼라 곱
	Vector2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
	/// 스칼라 나눗셈
	Vector2 operator/(float scalar) const { return { x / scalar, y / scalar }; }
	/// 벡터의 누적덧셈
	Vector2& operator+=(const Vector2& other)
	{
		x += other.x; y += other.y; return *this;
	}
	/// 벡터의 누적뺄셈
	Vector2& operator-=(const Vector2& other) {
		x -= other.x; y -= other.y; return *this;
	}
	/// 스칼라 누적곱
	Vector2& operator*=(float scalar) {
		x *= scalar; y *= scalar; return *this;
	}
	/// 스칼라 누적나눗셈
	Vector2& operator/=(float scalar) {
		x /= scalar; y /= scalar; return *this;
	}
	///임의접근 연산자 오버로딩
	float& operator[](int index)
	{
		return index == 0 ? x : y;
	}
	///임의 접근 연산자(읽기전용)
	const float& operator[](int index) const {
		return index == 0 ? x : y;
	}
	/// 벡터의 부호반전
	Vector2 operator-()const { return { -x,-y }; }
	/// 두 벡터가 같은지 비교
	bool operator==(const Vector2& other) const { return x == other.x && y == other.y; }
	/// 두 벡터가 다르면 true
	bool operator!=(const Vector2& other) const { return !(*this == other); }
	/// (0, 0) 벡터 반환
	static Vector2 Zero() { return { 0.0f, 0.0f }; }
	/// (1, 1) 벡터 반환
	static Vector2 One() { return { 1.0f, 1.0f }; }
	/// X축 단위 벡터 반환
	static Vector2 UnitX() { return { 1.0f, 0.0f }; }
	/// Y축 단위 벡터 반환
	static Vector2 UnitY() { return { 0.0f, 1.0f }; }
	/// 라디안 각도에서 방향 벡터 생성 (cos, sin)
	static Vector2 FromAngle(float radians) { return { std::cos(radians), std::sin(radians) }; }
	/// 벡터의 길이 반환
	float Length() const { return std::sqrt(x * x + y * y); }
	/// 벡터 길이의 제곱 반환 (루트 계산 없음)
	float LengthSq() const { return x * x + y * y; }
	/// 벡터의 정규화된 복사본 반환
	Vector2 Normalized() const 
	{
		float len = Length();
		return (len != 0) ? Vector2(x / len, y / len) : Vector2(0, 0);
	}
	/// 벡터 내적 계산
	float Dot(const Vector2& other) const { return x * other.x + y * other.y; }
	/// 선형 보간: this에서 target까지 t만큼 보간 (t ∈ [0,1])
	Vector2 Lerp(const Vector2& target, float t) const 
	{
		return (*this) + (target - *this) * t;
	}
	/// 두 벡터 사이 거리 계산
	float Distance(const Vector2& other) const { return (*this - other).Length(); }
	/// 거리의 제곱 반환 (루트 없음)
	float DistanceSq(const Vector2& other) const { return (*this - other).LengthSq(); }
	/// 벡터의 방향을 라디안으로 반환 (atan2)
	float Angle() const { return std::atan2(y, x); }
	/// 각 성분을 주어진 범위 내로 제한한 벡터 반환
	Vector2 Clamp(const Vector2& min, const Vector2& max) const
	{
		return { std::clamp(x, min.x, max.x), std::clamp(y, min.y, max.y) };
	}
	/// 벡터의 수직 방향 벡터 반환 (90도 회전)
	Vector2 Perpendicular() const { return { -y, x }; }
	/// 다른 벡터 방향으로 투영된 벡터 반환
	Vector2 ProjectOnto(const Vector2& target) const 
	{
		Vector2 norm = target.Normalized();
		return norm * (this->Dot(norm));
	}
	/// 주어진 법선에 대해 반사된 벡터 반환
	Vector2 Reflect(const Vector2& normal) const
	{
		return *this - normal * (2.0f * this->Dot(normal));
	}
	/// 외적 (2D의 경우 스칼라 반환)
	float Cross(const Vector2& other) const { return x * other.y - y * other.x; }
	/// 원소별 곱 (Hadamard Product)
	Vector2 HadamardProduct(const Vector2& other) const
	{
		return { x * other.x, y * other.y };
	}
	/// 각 성분의 절댓값 반환
	Vector2 Abs() const { return { std::fabs(x), std::fabs(y) }; }
	/// 각 성분마다 더 큰 값 선택
	//Vector2 Max(const Vector2& other) const { return { std::max(x, other.x), std::max(y, other.y) }; }
	/// 각 성분마다 더 작은 값 선택
	//Vector2 Min(const Vector2& other) const { return { std::min(x, other.x), std::min(y, other.y) }; }
	/// 벡터가 (0, 0)인지 확인
	bool IsZero() const { return x == 0.0f && y == 0.0f; }
	/// x 또는 y 중 하나라도 NaN인지 확인
	bool IsNaN() const { return std::isnan(x) || std::isnan(y); }
	/// (0, 0)과 매우 근접한 벡터인지 확인 (부동소수 안정성)
	bool IsNearlyZero(float epsilon = 1e-6f) const
	{
		return std::fabs(x) < epsilon && std::fabs(y) < epsilon;
	}
	/// 두 벡터 사이 각도 반환 (라디안)
	float AngleBetween(const Vector2& other) const
	{
		float dotProduct = this->Dot(other);
		float lengths = this->Length() * other.Length();
		if (lengths == 0.0f) return 0.0f;
		return std::acos(dotProduct / lengths);
	}
	/// 벡터를 주어진 라디안 각도로 회전시킨 결과 반환
	Vector2 Rotate(float angle) const
	{
		float cosA = std::cos(angle);
		float sinA = std::sin(angle);
		return {
			x * cosA - y * sinA,
			x * sinA + y * cosA
		};
	}
	///최대길이 제한 벡터
	Vector2 Truncate(float maxLength) const
	{
		float len = Length();
		return (len > maxLength) ? this->Normalized() * maxLength : *this;
	}
	/// 무한대로 늘어나는 지 체크(부동소수점 에러대비)
	bool IsFinite() const
	{
		return std::isfinite(x) && std::isfinite(y);
	}
	/// 자기자신을 정규화 할때 사용
	void Normalize() 
	{
		float len = Length();
		if (len != 0.0f) {
			x /= len;
			y /= len;
		}
	}
};