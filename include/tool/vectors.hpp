#pragma once

#include <cmath>
#include <iostream>

namespace exocet {
    template <typename T>
    class Vector2D {
        public:
            T x, y;

            Vector2D() { setPoints(0, 0); }
            Vector2D(T x, T y) { setPoints(x, y); }
            ~Vector2D() noexcept = default;

            static inline Vector2D magnitude2Vectors(const Vector2D& vector1, const Vector2D& vector2) { 
                return Vector2D(sqrt(vector1.x * vector1.x - vector2.x * vector2.x), sqrt(vector1.y * vector1.y - vector2.y * vector2.y));
            }
            static inline Vector2D distance2Vectors(const Vector2D& vector1, const Vector2D& vector2) {
                return Vector2D(vector2.x - vector1.x, vector2.y - vector1.y);
            }

            Vector2D clampMagnitude(T maxMag) const noexcept {
                T mag = magnitude();
                if (mag > maxMag) {
                    T scale = maxMag / mag;
                    return scalar(scale);
                }
                return Vector2D(x, y);
            }

            static inline Vector2D vectorZeros() { return Vector2D(0, 0); }

            inline bool isVectorNull() const noexcept { return (x == 0) && (y == 0); }

            inline Vector2D abs() const noexcept { return Vector2D(std::abs(x), std::abs(y)); }
            inline T magnitude() const noexcept { return static_cast<T>(std::hypot(x, y)); }
            inline Vector2D normalized() const noexcept { 
                T mag = magnitude();
                return (mag == 0)? Vector2D(0, 0): Vector2D(x / mag, y / mag); 
            }
            inline Vector2D perpendicular() const noexcept { return Vector2D(-y, x); }
            inline T dot(const Vector2D& vec) const noexcept { return x * vec.x + y * vec.y; }
            inline Vector2D scalar(const T alpha) const noexcept { return Vector2D(x * alpha, y * alpha); }
            inline Vector2D reflect() const noexcept { return Vector2D(-x, -y); }
            inline Vector2D rotate(double angle) const noexcept { return Vector2D(x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle)); }
            inline double getAngle() const noexcept { return std::atan2(x, y); }
            inline void setPoints(T x, T y) noexcept { this->x = x; this->y = y; }

            inline void add(const Vector2D& vector) noexcept { x += vector.x; y += vector.y; }
            inline void sub(const Vector2D& vector) noexcept { x -= vector.x; y -= vector.y; }
            inline void mul(const Vector2D& vector) noexcept { x *= vector.x; y *= vector.y; }
            inline void div(const Vector2D& vector) {
                if(vector.y == 0) throw std::runtime_error("cant divide by 0");
                x /= vector.x; 
                y /= vector.y; 
            }
            inline Vector2D divAlpha(T alpha) {
                if(alpha == 0) throw std::runtime_error("cant dive by 0");
                return Vector2D(x / alpha, y / alpha);
            }

            inline Vector2D operator+(const Vector2D& vec) const noexcept { return Vector2D(x + vec.x, y + vec.y); }
            inline Vector2D operator-(const Vector2D& vec) const noexcept { return Vector2D(x - vec.x, y - vec.y); }
            inline Vector2D operator*(const Vector2D& vec) const noexcept { return Vector2D(x * vec.x, y * vec.y); }
            inline Vector2D operator/(const Vector2D& vec) const {
                if(vec.y == 0) throw std::runtime_error("cant divide by 0");
                return Vector2D(x / vec.x, y / vec.y); 
            } 

            inline Vector2D operator+=(const Vector2D& vec) noexcept { add(vec); return *this; }
            inline Vector2D operator-=(const Vector2D& vec) noexcept { sub(vec); return *this; }
            inline Vector2D operator*=(const Vector2D& vec) noexcept { mul(vec); return *this; }
            inline Vector2D operator/=(const Vector2D& vec) { div(vec); return *this; }

            template <typename U>
            inline Vector2D<U> convert() const noexcept { return Vector2D<U>((U) x, (U) y); }

            inline friend std::ostream& operator<<(std::ostream& os, const Vector2D& vector) noexcept {
                return os << "(" << vector.x << "," << vector.y << ")";
            }
    };

    using DoubleVector2D = Vector2D<double>;
    using IntVector2D = Vector2D<int>;
    using FloatVector2D = Vector2D<float>;
}