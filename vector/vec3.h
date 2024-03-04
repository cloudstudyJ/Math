#pragma once

#include "../../Utility/typeHelper.h"

/** TODO LIST
 *      1. cross production return type decision
 *      2. dot production return type decision
 *      3. support floating points compare
 *      4. operator +, - type casting decision
*/

template <typename T, typename = enableIF<isArithmetic<T>>>
class Vec3 {
    public:
        Vec3();
        Vec3(const Vec3<T>& other);
        Vec3(Vec3<T>&& other) noexcept;
        ~Vec3() noexcept;

        template <typename U> Vec3(const U& x = { }, const U& y = { }, const U& z = { });

        Vec3& operator=(const Vec3<T>& other);
        Vec3& operator=(Vec3<T>&& other) noexcept;

        template <typename U> Vec3& operator+=(const Vec3<U>& other);
        template <typename U> Vec3& operator-=(const Vec3<U>& other);
        template <typename U> Vec3& operator/=(const U& scalar);
        template <typename U> Vec3& operator*=(const U& scalar);

        template <typename U> Vec3 operator+(const Vec3<U>& other) const;
        template <typename U> Vec3 operator-(const Vec3<U>& other) const;
        template <typename U> Vec3 operator/(const U& scalar) const;
        template <typename U> Vec3 operator*(const U& scalar) const;

        template <typename U> Vec3& operator()(const U& x, const U& y, const U& z);
        template <typename U> Vec3& operator()(const Vec3<U>& other);

        template <typename U> bool operator==(const Vec3<U>& other) const;
        template <typename U> bool operator!=(const Vec3<U>& other) const;
        template <typename U> bool operator<(const Vec3<U>& other) const;
        template <typename U> bool operator<=(const Vec3<U>& other) const;
        template <typename U> bool operator>(const Vec3<U>& other) const;
        template <typename U> bool operator>=(const Vec3<U>& other) const;

        template <typename U> T dot(const Vec3<U>& other) const;
        template <typename U> Vec3 cross(const Vec3<U>& other) const;

        template <typename U> void x(const U& x);
        template <typename U> void y(const U& y);
        template <typename U> void z(const U& z);

        T x() const noexcept;
        T y() const noexcept;
        T z() const noexcept;

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

template <typename T, typename E> Vec3<T, E>::Vec3() { }
template <typename T, typename E> Vec3<T, E>::Vec3(const Vec3<T>& other) { *this = other; }
template <typename T, typename E> Vec3<T, E>::Vec3(Vec3<T>&& other) noexcept { *this = move(other); }
template <typename T, typename E> Vec3<T, E>::~Vec3() noexcept { }

template <typename T, typename E> template <typename U>
Vec3<T, E>::Vec3(const U& x, const U& y, const U& z)
    : mX{static_cast<T>(x)}, mY{static_cast<T>(y)}, mZ{static_cast<T>(z)} { }

template <typename T, typename E>
Vec3<T, E>& Vec3<T, E>::operator=(const Vec3<T>& other) {
    mX = other.mX;
    mY = other.mY;
    mZ = other.mZ;

    return *this;
}
template <typename T, typename E>
Vec3<T, E>& Vec3<T, E>::operator=(Vec3<T>&& other) noexcept {
    mX = other.mX;
    mY = other.mY;
    mZ = other.mZ;

    other.mX = { };
    other.mY = { };
    other.mZ = { };

    return *this;
}

template <typename T, typename E> template <typename U>
Vec3<T, E>& Vec3<T, E>::operator/=(const U& scalar) {
    mX /= scalar;
    mY /= scalar;
    mZ /= scalar;

    return *this;
}
template <typename T, typename E> template <typename U>
Vec3<T, E>& Vec3<T, E>::operator*=(const U& scalar) {
    mX *= scalar;
    mY *= scalar;
    mZ *= scalar;

    return *this;
}

template <typename T, typename E> template <typename U>
Vec3<T, E> Vec3<T, E>::operator/(const U& scalar) const { return Vec3(mX / scalar, mY / scalar, mZ / scalar); }
template <typename T, typename E> template <typename U>
Vec3<T, E> Vec3<T, E>::operator*(const U& scalar) const { return Vec3(mX * scalar, mY * scalar, mZ * scalar); }

template <typename T, typename E> template <typename U>
Vec3<T, E>& Vec3<T, E>::operator()(const U& x, const U& y, const U& z) {
    mX = static_cast<T>(x);
    mY = static_cast<T>(y);
    mZ = static_cast<T>(z);

    return *this;
}
template <typename T, typename E> template <typename U>
Vec3<T, E>& Vec3<T, E>::operator()(const Vec3<U>& other) {
    mX = static_cast<T>(other.mX);
    mY = static_cast<T>(other.mY);
    mZ = static_cast<T>(other.mZ);

    return *this;
}



template <typename T, typename E> template <typename U>
void Vec3<T, E>::x(const U& x) { mX = static_cast<T>(x); }
template <typename T, typename E> template <typename U>
void Vec3<T, E>::y(const U& x) { mY = static_cast<T>(y); }
template <typename T, typename E> template <typename U>
void Vec3<T, E>::z(const U& z) { mZ = static_cast<T>(z); }

template <typename T, typename E>
T Vec3<T, E>::x() const noexcept { return mX; }
template <typename T, typename E>
T Vec3<T, E>::y() const noexcept { return mY; }
template <typename T, typename E>
T Vec3<T, E>::z() const noexcept { return mZ; }