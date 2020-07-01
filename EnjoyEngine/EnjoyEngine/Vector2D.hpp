#pragma once
#include <math.h>

namespace EE {
	template<typename T>
	struct Vector2D {
		T x;
		T y;

		Vector2D<T>& operator =(Vector2D<T> b) {
			x = b.x;
			y = b.y;
			return *this;
		}

		Vector2D<T> operator -(Vector2D<T> b) {
			Vector2D<T> temp{ x - b.x, y - b.y };
			return temp;
		}

		Vector2D<T> operator +(Vector2D<T> b) {
			Vector2D<T> temp{ x + b.x, y + b.y };
			return temp;
		}

		Vector2D<T> operator *(T b) {
			Vector2D<T> temp{ x * b, y * b };
			return temp;
		}

		Vector2D<T> operator /(T b) {
			Vector2D<T> temp{ x / b, y / b };
			return temp;
		}

		Vector2D<T>& operator +=(const Vector2D<T>& b) {
			x += b.x;
			y += b.y;
			return *this;
		}

		Vector2D<T>& operator -=(const Vector2D<T>& b) {
			x -= b.x;
			y -= b.y;
			return *this;
		}

		Vector2D<T>& operator *=(const T& b) {
			x *= b;
			y *= b;
			return *this;
		}

		Vector2D<T>& operator /=(const T& b) {
			x /= b;
			y /= b;
			return *this;
		}

		float magnitude() {
			return sqrtf(x * x + y * y);
		}

		Vector2D<T>& normalize() {
			float len = magnitude();
			if (len > 0.f) {
				x = x / len;
				y = y / len;
			}
			return *this;
		}

		Vector2D<T>& setMagnitude(float mag) {
			normalize();
			x = x * mag;
			y = y * mag;
			return *this;
		}

		float dot(Vector2D<T> b) {
			return x * b.x + y * b.y;
		}
	};
}
