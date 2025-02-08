#include "../../Include/RmlUi/Core/Math.h"
#include "../../Include/RmlUi/Core/Types.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

namespace Rml {

namespace Math {

	static constexpr float FZERO = 0.0001f;

	RMLUICORE_API bool IsCloseToZero(float value)
	{
		return Absolute(value) < FZERO;
	}

	RMLUICORE_API float Absolute(float value)
	{
		return fabsf(value);
	}

	RMLUICORE_API int Absolute(int value)
	{
		return abs(value);
	}

	RMLUICORE_API Vector2f Absolute(Vector2f value)
	{
		return {fabsf(value.x), fabsf(value.y)};
	}

	RMLUICORE_API float Cos(float angle)
	{
		return cosf(angle);
	}

	RMLUICORE_API float ACos(float value)
	{
		return acosf(value);
	}

	RMLUICORE_API float Sin(float angle)
	{
		return sinf(angle);
	}

	RMLUICORE_API float ASin(float value)
	{
		return asinf(value);
	}

	RMLUICORE_API float Tan(float angle)
	{
		return tanf(angle);
	}

	RMLUICORE_API float ATan2(float y, float x)
	{
		return atan2f(y, x);
	}

	RMLUICORE_API float Exp(float value)
	{
		return expf(value);
	}

	RMLUICORE_API int Log2(int value)
	{
		int result = 0;
		while (value > 1)
		{
			value >>= 1;
			result++;
		}
		return result;
	}

	RMLUICORE_API float RadiansToDegrees(float angle)
	{
		return angle * (180.0f / RMLUI_PI);
	}

	RMLUICORE_API float DegreesToRadians(float angle)
	{
		return angle * (RMLUI_PI / 180.0f);
	}

	RMLUICORE_API float NormaliseAngle(float angle)
	{
		float result = fmodf(angle, RMLUI_PI * 2.0f);
		if (result < 0.f)
			result += RMLUI_PI * 2.0f;
		return result;
	}

	RMLUICORE_API float SquareRoot(float value)
	{
		return sqrtf(value);
	}

	RMLUICORE_API float Round(float value)
	{
		return floorf(value + 0.5f);
	}

	RMLUICORE_API double Round(double value)
	{
		return floor(value + 0.5);
	}

	RMLUICORE_API float RoundUp(float value)
	{
		return ceilf(value);
	}

	RMLUICORE_API float RoundDown(float value)
	{
		return floorf(value);
	}

	RMLUICORE_API int RoundToInteger(float value)
	{
		if (value > 0.0f)
			return int(value + 0.5f);

		return int(value - 0.5f);
	}

	RMLUICORE_API int RoundUpToInteger(float value)
	{
		return int(ceilf(value));
	}

	RMLUICORE_API int RoundDownToInteger(float value)
	{
		return int(floorf(value));
	}

	RMLUICORE_API float DecomposeFractionalIntegral(float value, float* integral)
	{
		return modff(value, integral);
	}

	RMLUICORE_API void SnapToPixelGrid(float& offset, float& width)
	{
		const float right_edge = offset + width;
		offset = Math::Round(offset);
		width = Math::Round(right_edge) - offset;
	}

	RMLUICORE_API void SnapToPixelGrid(Vector2f& position, Vector2f& size)
	{
		const Vector2f bottom_right = position + size;
		position = position.Round();
		size = bottom_right.Round() - position;
	}

	RMLUICORE_API void ExpandToPixelGrid(Vector2f& position, Vector2f& size)
	{
		const Vector2f bottom_right = position + size;
		position = Vector2f(std::floor(position.x), std::floor(position.y));
		size = Vector2f(std::ceil(bottom_right.x), std::ceil(bottom_right.y)) - position;
	}

	RMLUICORE_API int ToPowerOfTwo(int number)
	{
		// Check if the number is already a power of two.
		if ((number & (number - 1)) == 0)
			return number;

		// Assuming 31 useful bits in an int here ... !
		for (int i = 31; i >= 0; i--)
		{
			if (number & (1 << i))
			{
				if (i == 31)
					return 1 << 31;
				else
					return 1 << (i + 1);
			}
		}

		return 0;
	}

	RMLUICORE_API int HexToDecimal(char hex_digit)
	{
		if (hex_digit >= '0' && hex_digit <= '9')
			return hex_digit - '0';
		else if (hex_digit >= 'a' && hex_digit <= 'f')
			return 10 + (hex_digit - 'a');
		else if (hex_digit >= 'A' && hex_digit <= 'F')
			return 10 + (hex_digit - 'A');

		return -1;
	}

	RMLUICORE_API float RandomReal(float max_value)
	{
		return (rand() / (float)RAND_MAX) * max_value;
	}

	RMLUICORE_API int RandomInteger(int max_value)
	{
		return (rand() % max_value);
	}

	RMLUICORE_API bool RandomBool()
	{
		return RandomInteger(2) == 1;
	}

	template <>
	Vector2f Max<Vector2f>(Vector2f a, Vector2f b)
	{
		return Vector2f(Max(a.x, b.x), Max(a.y, b.y));
	}
	template <>
	Vector2i Max<Vector2i>(Vector2i a, Vector2i b)
	{
		return Vector2i(Max(a.x, b.x), Max(a.y, b.y));
	}

	template <>
	Vector2f Min<Vector2f>(Vector2f a, Vector2f b)
	{
		return Vector2f(Min(a.x, b.x), Min(a.y, b.y));
	}
	template <>
	Vector2i Min<Vector2i>(Vector2i a, Vector2i b)
	{
		return Vector2i(Min(a.x, b.x), Min(a.y, b.y));
	}

	template <>
	Vector2f Clamp(Vector2f value, Vector2f min, Vector2f max)
	{
		return Vector2f(Clamp(value.x, min.x, max.x), Clamp(value.y, min.y, max.y));
	}
	template <>
	Vector2i Clamp(Vector2i value, Vector2i min, Vector2i max)
	{
		return Vector2i(Clamp(value.x, min.x, max.x), Clamp(value.y, min.y, max.y));
	}

} // namespace Math
} // namespace Rml
