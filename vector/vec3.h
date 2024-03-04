#pragma once

#include "../../Utility/typeHelper.h"

/** TODO LIST
 *      1. cross production return type decision
 *      2. dot production return type decision
*/

template <typename T, typename = enableIF<isArithmetic<T>>>
class Vec3 {
    public:
        Vec3();
        Vec3(const Vec3& other);
        Vec3(Vec3&& other) noexcept;
        ~Vec3() noexcept;

        template <typename U> Vec3(const U& x, const U& y, const U& z);

        Vec3& operator=(const Vec3& other);
        Vec3& operator=(Vec3&& other) noexcept;

        template <typename U> Vec3& operator+=(const Vec3<U>& other);
        template <typename U> Vec3& operator-=(const Vec3<U>& other);
        template <typename U> Vec3& operator/=(const U& scalar);
        template <typename U> Vec3& operator*=(const U& scalar);

        template <typename U> Vec3 operator+(const Vec3<U>& other) const;
        template <typename U> Vec3 operator-(const Vec3<U>& other) const;
        template <typename U> Vec3 operator/(const U& scalar) const;
        template <typename U> Vec3 operator*(const U& scalar) const;

        template <typename U> bool operator==(const Vec3<U>& other) const;
        template <typename U> bool operator!=(const Vec3<U>& other) const;
        template <typename U> bool operator<(const Vec3<U>& other) const;
        template <typename U> bool operator<=(const Vec3<U>& other) const;
        template <typename U> bool operator>(const Vec3<U>& other) const;
        template <typename U> bool operator>=(const Vec3<U>& other) const;

        template <typename U> Vec3& operator()(const U& x, const U& y, const U& z);
        template <typename U> Vec3& operator()(const Vec3<U>& other);

        template <typename U> T dot(const Vec3<U>& other) const;
        template <typename U> Vec3 cross(const Vec3<U>& other) const;

        template <typename U> void x(const U& x);
        template <typename U> void y(const U& y);
        template <typename U> void z(const U& z);
        template <typename U> inline void r(const U& x);
        template <typename U> inline void g(const U& y);
        template <typename U> inline void b(const U& z);

        T x() const noexcept;
        T y() const noexcept;
        T z() const noexcept;
        inline T r() const noexcept;
        inline T g() const noexcept;
        inline T b() const noexcept;

        template <typename U> static T dot(const Vec3<T>& v1, const Vec3<U>& v2);
        template <typename U> static Vec3 cross(const Vec3<T>& v1, const Vec3<U>& v2);

    private:
        union {
            T mX{ };
            T mR;
        };
        union {
            T mY{ };
            T mG;
        };
        union {
            T mZ{ };
            T mB;
        };
};