﻿namespace Rml {

template <typename Type>
Vector2<Type>::Vector2() : x{}, y{}
{}

template <typename Type>
Vector2<Type>::Vector2(Type v) : x(v), y(v)
{}

template <typename Type>
Vector2<Type>::Vector2(Type x, Type y) : x(x), y(y)
{}

template <typename Type>
float Vector2<Type>::Magnitude() const
{
	return Math::SquareRoot(static_cast<float>(SquaredMagnitude()));
}

template <typename Type>
Type Vector2<Type>::SquaredMagnitude() const
{
	return x * x + y * y;
}

template <typename Type>
inline Vector2<Type> Vector2<Type>::Normalise() const
{
	static_assert(std::is_same<Type, float>::value, "Normalise only implemented for Vector<float>.");
	return *this;
}

template <>
inline Vector2<float> Vector2<float>::Normalise() const
{
	const float magnitude = Magnitude();
	if (Math::IsCloseToZero(magnitude))
		return *this;

	return *this / magnitude;
}

template <>
inline Vector2<float> Vector2<float>::Round() const
{
	Vector2<float> result;
	result.x = Math::Round(x);
	result.y = Math::Round(y);
	return result;
}

template <>
inline Vector2<int> Vector2<int>::Round() const
{
	return *this;
}

template <typename Type>
Type Vector2<Type>::DotProduct(Vector2 rhs) const
{
	return x * rhs.x + y * rhs.y;
}

template <typename Type>
Vector2<Type> Vector2<Type>::Rotate(float theta) const
{
	float cos_theta = Math::Cos(theta);
	float sin_theta = Math::Sin(theta);

	return Vector2<Type>(((Type)(cos_theta * x - sin_theta * y)), ((Type)(sin_theta * x + cos_theta * y)));
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator-() const
{
	return Vector2(-x, -y);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator+(Vector2 rhs) const
{
	return Vector2<Type>(x + rhs.x, y + rhs.y);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator-(Vector2 rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator*(Type rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator*(Vector2 rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator/(Type rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

template <typename Type>
Vector2<Type> Vector2<Type>::operator/(Vector2 rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator+=(Vector2 rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator-=(Vector2 rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator*=(Type rhs)
{
	x *= rhs;
	y *= rhs;

	return *this;
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator*=(Vector2 rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator/=(Type rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}

template <typename Type>
Vector2<Type>& Vector2<Type>::operator/=(Vector2 rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

template <typename Type>
bool Vector2<Type>::operator==(Vector2 rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

template <typename Type>
bool Vector2<Type>::operator!=(Vector2 rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

template <typename Type>
Vector2<Type>::operator const Type*() const
{
	return &x;
}

template <typename Type>
Vector2<Type>::operator Type*()
{
	return &x;
}

template <typename Type>
template <typename U>
inline Vector2<Type>::operator Vector2<U>() const
{
	return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
}

template <typename Type>
inline Vector2<Type> operator*(Type lhs, Vector2<Type> rhs)
{
	return rhs * lhs;
}

} // namespace Rml
