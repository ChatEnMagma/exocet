#pragma once

#include <cmath>
#include <iostream>

#include "constantes.hpp"

namespace exocet {
    template <typename T>
    class Vector2D {
        public:
            T x, y;

            Vector2D() { setPoints(0, 0); }
            Vector2D(T x, T y) { setPoints(x, y); }

            static inline T twoVectorsMagnitude(const Vector2D& vector1, const Vector2D& vector2) { return abs(vector2.x - vector1.x) + abs(vector2.y - vector1.y); }

            inline T magnitude() const { return sqrt(x * x + y * y); }
            inline Vector2D normalized() const { 
                T mag = magnitude();
                if(mag == 0) return Vector2D(0, 0);
                return Vector2D(x / mag, y / mag); 
            }
            inline Vector2D perpendicular() const { return Vector2D(-y, x); }
            inline T dot(Vector2D<T> vec) { return x * vec.x + y * vec.y; }
            inline Vector2D scalar(const T alpha) const { return Vector2D(x * alpha, y * alpha); }
            inline Vector2D reflect() const { return Vector2D(-x, -y); }
            inline Vector2D rotate(double angle) const { return Vector2D(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }
            inline double getAngle() const { return atan2(x, y); }
            inline void setPoints(T x, T y) { this->x = x; this->y = y; }

            inline void add(const Vector2D& vector) { x += vector.x; y += vector.y; }
            inline void sub(const Vector2D& vector) { x -= vector.x; y -= vector.y; }
            inline void mul(const Vector2D& vector) { x *= vector.x; y *= vector.y; }
            inline void div(const Vector2D& vector) { x /= vector.x; y /= vector.y; }

            inline Vector2D operator+(const Vector2D& vec) const { return Vector2D(x + vec.x, y + vec.y); }
            inline Vector2D operator-(const Vector2D& vec) const { return Vector2D(x - vec.x, y - vec.y); }
            inline Vector2D operator*(const Vector2D& vec) const { return Vector2D(x * vec.x, y * vec.y); }
            inline Vector2D operator/(const Vector2D& vec) const { return Vector2D(x / vec.x, y / vec.y); } 

            inline Vector2D operator+=(const Vector2D& vec) { add(vec); return *this; }
            inline Vector2D operator-=(const Vector2D& vec) { sub(vec); return *this; }
            inline Vector2D operator*=(const Vector2D& vec) { mul(vec); return *this; }
            inline Vector2D operator/=(const Vector2D& vec) { div(vec); return *this; }

            template <typename U>
            inline Vector2D<U> convert() const { return Vector2D<U>((U) x, (U) y); }

            inline friend std::ostream& operator<<(std::ostream& os, const Vector2D<T>& vector) {
                if constexpr(std::is_same_v<std::decay_t<T>, sol::object>) {
                    sol::object xO = static_cast<sol::object>(vector.x);
                    sol::object yO = static_cast<sol::object>(vector.y);

                    return os << "(" << xO.as<double>() << "," << yO.as<double>() << ")";
                } else {
                    return os << "(" << vector.x << "," << vector.y << ")";
                }
            }
    };
}