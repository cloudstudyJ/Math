#pragma once

#include "../base.hpp"
#include "../math.hpp"
#include "../typeHandler.hpp"

#include <cassert>      // assert()
#include <cmath>        // sqrt()

template <typename T>
class Vec<T, 2> {
    public:
        Vec() noexcept;
        Vec(const Vec<T, 2>&) noexcept;
        Vec(Vec<T, 2>&&) noexcept;
        ~Vec() noexcept;

        template <typename U> Vec(const Vec<U, 2>&) noexcept;
        template <typename U> Vec(Vec<U, 2>&&) noexcept;

        template <typename U>
        Vec(const U&) noexcept;
        template <typename U1, typename U2>
        Vec(const U1&, const U2&) noexcept;

        Vec<T, 2>& operator=(const Vec<T, 2>&) noexcept;
        Vec<T, 2>& operator=(Vec<T, 2>&&) noexcept;

        template <typename U> Vec<T, 2>& operator=(const Vec<U, 2>&) noexcept;
        template <typename U> Vec<T, 2>& operator=(Vec<U, 2>&&) noexcept;

        template <typename U>
        Vec<T, 2>& operator()(const Vec<U, 2>&) noexcept;
        template <typename U>
        Vec<T, 2>& operator()(const U&) noexcept;
        template <typename U1, typename U2>
        Vec<T, 2>& operator()(const U1&, const U2&) noexcept;

        T& operator[](const unsigned int& idx);
        const T& operator[](const unsigned int& idx) const;

        template <typename U> Vec<T, 2>& operator+=(const Vec<U, 2>&) noexcept;
        template <typename U> Vec<T, 2>& operator-=(const Vec<U, 2>&) noexcept;
        template <typename U> Vec<T, 2>& operator*=(const U&) noexcept;
        template <typename U> Vec<T, 2>& operator/=(const U&);

        template <typename U> inline Vec<T, 2> operator+(const Vec<U, 2>&) const noexcept;
        template <typename U> inline Vec<T, 2> operator-(const Vec<U, 2>&) const noexcept;
        template <typename U> inline Vec<T, 2> operator*(const U&) const noexcept;
        template <typename U> inline Vec<T, 2> operator/(const U&) const;

        template <typename U> inline constexpr T dot(const Vec<U, 2>&) const noexcept;
        template <typename U> inline constexpr T cross(const Vec<U, 2>&) const noexcept;

        inline Vec<T, 2> normalize() const noexcept;
        inline constexpr T length() const noexcept;
        inline constexpr T lengthSquare() const noexcept;

        template <typename U> static inline constexpr T dot(const Vec<T, 2>&, const Vec<U, 2>&) noexcept;
        template <typename U> static inline constexpr T cross(const Vec<T, 2>&, const Vec<U, 2>&) noexcept;

        static inline Vec<T, 2> normalize(const Vec<T, 2>&) noexcept;
        static inline constexpr T length(const Vec<T, 2>&) noexcept;
        static inline constexpr T lengthSquare(const Vec<T, 2>&) noexcept;

    public:
        union { T x{ }, s; };
        union { T y{ }, t; };
};
template <typename T> using Vec2 = Vec<T, 2>;

template <typename T> Vec<T, 2>::Vec() noexcept { }
template <typename T> Vec<T, 2>::Vec(const Vec<T, 2>& other) noexcept { *this = other; }
template <typename T> Vec<T, 2>::Vec(Vec<T, 2>&& other) noexcept { *this = move(other); }
template <typename T> Vec<T, 2>::~Vec() noexcept { }

template <typename T> template <typename U>
Vec<T, 2>::Vec(const Vec<U, 2>& other) noexcept { *this = other; }
template <typename T> template <typename U>
Vec<T, 2>::Vec(Vec<U, 2>&& other) noexcept { *this = move(other); }

template <typename T> template <typename U>
Vec<T, 2>::Vec(const U& _x) noexcept { (*this)(_x); }
template <typename T> template <typename U1, typename U2>
Vec<T, 2>::Vec(const U1& _x, const U2& _y) noexcept { (*this)(_x, _y); }

template <typename T> Vec<T, 2>& Vec<T, 2>::operator=(const Vec<T, 2>& other) noexcept {
    x = other.x;
    y = other.y;

    return *this;
}
template <typename T> Vec<T, 2>& Vec<T, 2>::operator=(Vec<T, 2>&& other) noexcept {
    x = other.x;
    y = other.y;

    other.x = { };
    other.y = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator=(const Vec<U, 2>& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator=(Vec<U, 2>&& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);

    other.x = { };
    other.y = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator()(const Vec<U, 2>& other) noexcept { return (*this = other); }
template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator()(const U& _x) noexcept {
    x = static_cast<T>(_x);

    return *this;
}
template <typename T> template <typename U1, typename U2>
Vec<T, 2>& Vec<T, 2>::operator()(const U1& _x, const U2& _y) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);

    return *this;
}

template <typename T> T& Vec<T, 2>::operator[](const unsigned int& idx) {
    assert(idx < 2);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
    }
}
template <typename T> const T& Vec<T, 2>::operator[](const unsigned int& idx) const {
    assert(idx < 2);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
    }
}

template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator+=(const Vec<U, 2>& other) noexcept {
    x = static_cast<T>(x + other.x);
    y = static_cast<T>(y + other.y);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator-=(const Vec<U, 2>& other) noexcept {
    x = static_cast<T>(x - other.x);
    y = static_cast<T>(y - other.y);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator*=(const U& val) noexcept {
    x = static_cast<T>(x * val);
    y = static_cast<T>(y * val);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 2>& Vec<T, 2>::operator/=(const U& val) {
    assert(!Math::isZero(val));

    x = static_cast<T>(x / val);
    y = static_cast<T>(y / val);

    return *this;
}

template <typename T> template <typename U>
inline Vec<T, 2> Vec<T, 2>::operator+(const Vec<U, 2>& other) const noexcept {
    return {
        static_cast<T>(x + other.x),
        static_cast<T>(y + other.y)
    };
}
template <typename T> template <typename U>
inline Vec<T, 2> Vec<T, 2>::operator-(const Vec<U, 2>& other) const noexcept {
    return {
        static_cast<T>(x - other.x),
        static_cast<T>(y - other.y)
    };
}
template <typename T> template <typename U>
inline Vec<T, 2> Vec<T, 2>::operator*(const U& val) const noexcept {
    return {
        static_cast<T>(x * val),
        static_cast<T>(y * val)
    };
}
template <typename T> template <typename U>
inline Vec<T, 2> Vec<T, 2>::operator/(const U& val) const {
    assert(!Math::isZero(val));

    return {
        static_cast<T>(x / val),
        static_cast<T>(y / val)
    };
}

template <typename T> template <typename U>
inline constexpr T Vec<T, 2>::dot(const Vec<U, 2>& other) const noexcept { return static_cast<T>(x * other.x + y * other.y); }
template <typename T> template <typename U>
inline constexpr T Vec<T, 2>::cross(const Vec<U, 2>& other) const noexcept { return static_cast<T>(x * other.y - y * other.x); }

template <typename T> inline Vec<T, 2> Vec<T, 2>::normalize() const noexcept { return (*this / length()); }
template <typename T> inline constexpr T Vec<T, 2>::length() const noexcept { return static_cast<T>(std::sqrt(lengthSquare())); }
template <typename T> inline constexpr T Vec<T, 2>::lengthSquare() const noexcept { return (Math::square(x) + Math::square(y)); }

template <typename T> template <typename U>
inline constexpr T Vec<T, 2>::dot(const Vec<T, 2>& v1, const Vec<U, 2>& v2) noexcept { return v1.dot(v2); }
template <typename T> template <typename U>
inline constexpr T Vec<T, 2>::cross(const Vec<T, 2>& v1, const Vec<U, 2>& v2) noexcept { return v1.cross(v2); }

template <typename T> inline Vec<T, 2> Vec<T, 2>::normalize(const Vec<T, 2>& v) noexcept { return v.normalize(); }
template <typename T> inline constexpr T Vec<T, 2>::length(const Vec<T, 2>& v) noexcept { return v.length(); }
template <typename T> inline constexpr T Vec<T, 2>::lengthSquare(const Vec<T, 2>& v) noexcept { return v.lengthSquare(); }