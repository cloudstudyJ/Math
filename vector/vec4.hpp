#pragma once

#include "../base.hpp"
#include "../math.hpp"
#include "../typeHandler.hpp"

#include <cassert>      // assert()
#include <cmath>        // sqrt()

template <typename T>
class Vec<T, 4> {
    public:
        Vec() noexcept;
        Vec(const Vec<T, 4>&) noexcept;
        Vec(Vec<T, 4>&&) noexcept;
        ~Vec() noexcept;

        template <typename U> Vec(const Vec<U, 4>&) noexcept;
        template <typename U> Vec(Vec<U, 4>&&) noexcept;

        template <typename U>
        Vec(const U&) noexcept;
        template <typename U1, typename U2>
        Vec(const U1&, const U2&) noexcept;
        template <typename U1, typename U2, typename U3>
        Vec(const U1&, const U2&, const U3&) noexcept;
        template <typename U1, typename U2, typename U3, typename U4>
        Vec(const U1&, const U2&, const U3&, const U4&) noexcept;

        Vec<T, 4>& operator=(const Vec<T, 4>&) noexcept;
        Vec<T, 4>& operator=(Vec<T, 4>&&) noexcept;

        template <typename U> Vec<T, 4>& operator=(const Vec<U, 4>&) noexcept;
        template <typename U> Vec<T, 4>& operator=(Vec<U, 4>&&) noexcept;

        template <typename U>
        Vec<T, 4>& operator()(const Vec<U, 4>&) noexcept;
        template <typename U>
        Vec<T, 4>& operator()(const U&) noexcept;
        template <typename U1, typename U2>
        Vec<T, 4>& operator()(const U1&, const U2&) noexcept;
        template <typename U1, typename U2, typename U3>
        Vec<T, 4>& operator()(const U1&, const U2&, const U3&) noexcept;
        template <typename U1, typename U2, typename U3, typename U4>
        Vec<T, 4>& operator()(const U1&, const U2&, const U3&, const U4&) noexcept;

        T& operator[](const unsigned int& idx);
        const T& operator[](const unsigned int& idx) const;

        template <typename U> Vec<T, 4>& operator+=(const Vec<U, 4>&) noexcept;
        template <typename U> Vec<T, 4>& operator-=(const Vec<U, 4>&) noexcept;
        template <typename U> Vec<T, 4>& operator+=(const U&) noexcept;
        template <typename U> Vec<T, 4>& operator-=(const U&) noexcept;
        template <typename U> Vec<T, 4>& operator*=(const U&) noexcept;
        template <typename U> Vec<T, 4>& operator/=(const U&);

        template <typename U> inline Vec<T, 4> operator+(const Vec<U, 4>&) const noexcept;
        template <typename U> inline Vec<T, 4> operator-(const Vec<U, 4>&) const noexcept;
        template <typename U> inline Vec<T, 4> operator+(const U&) const noexcept;
        template <typename U> inline Vec<T, 4> operator-(const U&) const noexcept;
        template <typename U> inline Vec<T, 4> operator*(const U&) const noexcept;
        template <typename U> inline Vec<T, 4> operator/(const U&) const;

        template <typename U> inline constexpr T dot(const Vec<U, 4>&) const noexcept;

        inline Vec<T, 4> normalize() const noexcept;
        inline constexpr T length() const noexcept;
        inline constexpr T lengthSquare() const noexcept;

        template <typename U> static inline constexpr T dot(const Vec<T, 4>&, const Vec<U, 4>&) noexcept;

        static inline Vec<T, 4> normalize(const Vec<T, 4>&) noexcept;
        static inline constexpr T length(const Vec<T, 4>&) noexcept;
        static inline constexpr T lengthSquare(const Vec<T, 4>&) noexcept;

    public:
        union { T x{ }, r; };
        union { T y{ }, g; };
        union { T z{ }, b; };
        union { T w{ }, a; };
};
template <typename T> using Vec4 = Vec<T, 4>;

template <typename T> Vec<T, 4>::Vec() noexcept { }
template <typename T> Vec<T, 4>::Vec(const Vec<T, 4>& other) noexcept { *this = other; }
template <typename T> Vec<T, 4>::Vec(Vec<T, 4>&& other) noexcept { *this = move(other); }
template <typename T> Vec<T, 4>::~Vec() noexcept { }

template <typename T> template <typename U>
Vec<T, 4>::Vec(const Vec<U, 4>& other) noexcept { *this = other; }
template <typename T> template <typename U>
Vec<T, 4>::Vec(Vec<U, 4>&& other) noexcept { *this = move(other); }

template <typename T> template <typename U>
Vec<T, 4>::Vec(const U& _x) noexcept { (*this)(_x); }
template <typename T> template <typename U1, typename U2>
Vec<T, 4>::Vec(const U1& _x, const U2& _y) noexcept { (*this)(_x, _y); }
template <typename T> template <typename U1, typename U2, typename U3>
Vec<T, 4>::Vec(const U1& _x, const U2& _y, const U3& _z) noexcept { (*this)(_x, _y, _z); }
template <typename T> template <typename U1, typename U2, typename U3, typename U4>
Vec<T, 4>::Vec(const U1& _x, const U2& _y, const U3& _z, const U4& _w) noexcept { (*this)(_x, _y, _z, _w); }

template <typename T> Vec<T, 4>& Vec<T, 4>::operator=(const Vec<T, 4>& other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;
}
template <typename T> Vec<T, 4>& Vec<T, 4>::operator=(Vec<T, 4>&& other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    other.x = { };
    other.y = { };
    other.z = { };
    other.w = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator=(const Vec<U, 4>& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);
    w = static_cast<T>(other.w);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator=(Vec<U, 4>&& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);
    w = static_cast<T>(other.w);

    other.x = { };
    other.y = { };
    other.z = { };
    other.w = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator()(const Vec<U, 4>& other) noexcept { return (*this = other); }
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator()(const U& _x) noexcept {
    x = static_cast<T>(_x);

    return *this;
}
template <typename T> template <typename U1, typename U2>
Vec<T, 4>& Vec<T, 4>::operator()(const U1& _x, const U2& _y) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);

    return *this;
}
template <typename T> template <typename U1, typename U2, typename U3>
Vec<T, 4>& Vec<T, 4>::operator()(const U1& _x, const U2& _y, const U3& _z) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);
    z = static_cast<T>(_z);

    return *this;
}
template <typename T> template <typename U1, typename U2, typename U3, typename U4>
Vec<T, 4>& Vec<T, 4>::operator()(const U1& _x, const U2& _y, const U3& _z, const U4& _w) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);
    z = static_cast<T>(_z);
    w = static_cast<T>(_w);

    return *this;
}

template <typename T> T& Vec<T, 4>::operator[](const unsigned int& idx) {
    assert(idx < 4);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}
template <typename T> const T& Vec<T, 4>::operator[](const unsigned int& idx) const {
    assert(idx < 4);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
    }
}

template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator+=(const Vec<U, 4>& other) noexcept {
    x = static_cast<T>(x + other.x);
    y = static_cast<T>(y + other.y);
    z = static_cast<T>(z + other.z);
    w = static_cast<T>(w + other.w);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator-=(const Vec<U, 4>& other) noexcept {
    x = static_cast<T>(x - other.x);
    y = static_cast<T>(y - other.y);
    z = static_cast<T>(z - other.z);
    w = static_cast<T>(w - other.w);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator+=(const U& val) noexcept {
    x = static_cast<T>(x + val);
    y = static_cast<T>(y + val);
    z = static_cast<T>(z + val);
    w = static_cast<T>(w + val);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator-=(const U& val) noexcept {
    x = static_cast<T>(x - val);
    y = static_cast<T>(y - val);
    z = static_cast<T>(z - val);
    w = static_cast<T>(w - val);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator*=(const U& val) noexcept {
    x = static_cast<T>(x * val);
    y = static_cast<T>(y * val);
    z = static_cast<T>(z * val);
    w = static_cast<T>(w * val);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 4>& Vec<T, 4>::operator/=(const U& val) {
    assert(!Math::isZero(val));

    x = static_cast<T>(x / val);
    y = static_cast<T>(y / val);
    z = static_cast<T>(z / val);
    w = static_cast<T>(w / val);

    return *this;
}

template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator+(const Vec<U, 4>& other) const noexcept {
    return {
        static_cast<T>(x + other.x),
        static_cast<T>(y + other.y),
        static_cast<T>(z + other.z),
        static_cast<T>(w + other.w)
    };
}
template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator-(const Vec<U, 4>& other) const noexcept {
    return {
        static_cast<T>(x - other.x),
        static_cast<T>(y - other.y),
        static_cast<T>(z - other.z),
        static_cast<T>(w - other.w)
    };
}
template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator+(const U& val) const noexcept {
    return {
        static_cast<T>(x + val),
        static_cast<T>(y + val),
        static_cast<T>(z + val),
        static_cast<T>(w + val)
    };
}
template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator-(const U& val) const noexcept {
    return {
        static_cast<T>(x - val),
        static_cast<T>(y - val),
        static_cast<T>(z - val),
        static_cast<T>(w - val)
    };
}
template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator*(const U& val) const noexcept {
    return {
        static_cast<T>(x * val),
        static_cast<T>(y * val),
        static_cast<T>(z * val),
        static_cast<T>(w * val)
    };
}
template <typename T> template <typename U>
inline Vec<T, 4> Vec<T, 4>::operator/(const U& val) const {
    assert(!Math::isZero(val));

    return {
        static_cast<T>(x / val),
        static_cast<T>(y / val),
        static_cast<T>(z / val),
        static_cast<T>(w / val)
    };
}

template <typename T> template <typename U>
inline constexpr T Vec<T, 4>::dot(const Vec<U, 4>& other) const noexcept {
    return static_cast<T>(
        x * other.x +
        y * other.y +
        z * other.z +
        w * other.w
    );
}

template <typename T> inline Vec<T, 4> Vec<T, 4>::normalize() const noexcept { return (*this / length()); }
template <typename T> inline constexpr T Vec<T, 4>::length() const noexcept { return static_cast<T>(std::sqrt(lengthSquare())); }
template <typename T> inline constexpr T Vec<T, 4>::lengthSquare() const noexcept {
    return (
        Math::square(x) +
        Math::square(y) +
        Math::square(z) +
        Math::square(w)
    );
}

template <typename T> template <typename U>
inline constexpr T Vec<T, 4>::dot(const Vec<T, 4>& v1, const Vec<U, 4>& v2) noexcept { return v1.dot(v2); }

template <typename T> inline Vec<T, 4> Vec<T, 4>::normalize(const Vec<T, 4>& v) noexcept { return v.normalize(); }
template <typename T> inline constexpr T Vec<T, 4>::length(const Vec<T, 4>& v) noexcept { return v.length(); }
template <typename T> inline constexpr T Vec<T, 4>::lengthSquare(const Vec<T, 4>& v) noexcept { return v.lengthSquare(); }