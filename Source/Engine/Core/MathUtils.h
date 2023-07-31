#pragma once
#include <cmath>
namespace kiko
{
	constexpr float pi = 3.14159265358979f;
	constexpr float twoPi = 3.14159265358979f * 2;
	constexpr float hlfPi = 3.141592653589793f / 2;

	constexpr float RadiansToDegree(float radians) { return radians * 180.0f / pi; }
	constexpr float DegreestoRadians(float degrees) { return degrees * pi / 180.0f; }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b) {
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b) {
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max) {
//		if (min > max) std::swap(min,max);

		return (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) // t = 0 <-> 1
	{
		return (a * (1.0f - t)) + (b * t);
	}
}