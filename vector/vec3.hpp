#pragma once

#include "base.hpp"
#include "typeHandler.hpp"

#include <assert.h>     // assert()

template <typename T>
class Vec<T, 3> {
    public:
        Vec() noexcept;
        Vec(const Vec<T, 3>&) noexcept;
        Vec(Vec<T, 3>&&) noexcept;
        ~Vec() noexcept;

        template <typename U>
        Vec(const Vec<U, 3>&) noexcept;
        template <typename U>
        Vec(Vec<U, 3>&&) noexcept;

        template <typename U>
        Vec(const U&) noexcept;
        template <typename U1, typename U2>
        Vec(const U1&, const U2&) noexcept;
        template <typename U1, typename U2, typename U3>
        Vec(const U1&, const U2&, const U3&) noexcept;

        Vec<T, 3>& operator=(const Vec<T, 3>&) noexcept;
        Vec<T, 3>& operator=(Vec<T, 3>&&) noexcept;

        template <typename U>
        Vec<T, 3>& operator=(const Vec<U, 3>&) noexcept;
        template <typename U>
        Vec<T, 3>& operator=(Vec<U, 3>&&) noexcept;

        template <typename U>
        Vec<T, 3>& operator()(const Vec<U, 3>&) noexcept;
        template <typename U>
        Vec<T, 3>& operator()(const U&) noexcept;
        template <typename U1, typename U2>
        Vec<T, 3>& operator()(const U1&, const U2&) noexcept;
        template <typename U1, typename U2, typename U3>
        Vec<T, 3>& operator()(const U1&, const U2&, const U3&) noexcept;

        T& operator[](const unsigned int& idx);
        const T& operator[](const unsigned int& idx) const;

        template <typename U>
        inline constexpr T dot(const Vec<U, 3>&) const noexcept;
        template <typename U>
        inline Vec<T, 3> cross(const Vec<U, 3>&) const noexcept;

        template <typename U>
        static inline constexpr T dot(const Vec<T, 3>&, const Vec<U, 3>&) noexcept;
        template <typename U>
        static inline Vec<T, 3> cross(const Vec<T, 3>&, const Vec<U, 3>&) noexcept;

    public:
        union { T x{ }, r; };
        union { T y{ }, g; };
        union { T z{ }, b; };
};
template <typename T> using Vec3 = Vec<T, 3>;

template <typename T> Vec<T, 3>::Vec() noexcept { }
template <typename T> Vec<T, 3>::Vec(const Vec<T, 3>& other) noexcept { *this = other; }
template <typename T> Vec<T, 3>::Vec(Vec<T, 3>&& other) noexcept { *this = move(other); }
template <typename T> Vec<T, 3>::~Vec() noexcept { }

template <typename T> template <typename U>
Vec<T, 3>::Vec(const Vec<U, 3>& other) noexcept { *this = other; }
template <typename T> template <typename U>
Vec<T, 3>::Vec(Vec<U, 3>&& other) noexcept { *this = move(other); }

template <typename T> template <typename U>
Vec<T, 3>::Vec(const U& _x) noexcept { (*this)(_x); }
template <typename T> template <typename U1, typename U2>
Vec<T, 3>::Vec(const U1& _x, const U2& _y) noexcept { (*this)(_x, _y); }
template <typename T> template <typename U1, typename U2, typename U3>
Vec<T, 3>::Vec(const U1& _x, const U2& _y, const U3& _z) noexcept { (*this)(_x, _y, _z); }

template <typename T> Vec<T, 3>& Vec<T, 3>::operator=(const Vec<T, 3>& other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}
template <typename T> Vec<T, 3>& Vec<T, 3>::operator=(Vec<T, 3>&& other) noexcept {
    x = other.x;
    y = other.y;
    z = other.z;

    other.x = { };
    other.y = { };
    other.z = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 3>& Vec<T, 3>::operator=(const Vec<U, 3>& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);

    return *this;
}
template <typename T> template <typename U>
Vec<T, 3>& Vec<T, 3>::operator=(Vec<U, 3>&& other) noexcept {
    x = static_cast<T>(other.x);
    y = static_cast<T>(other.y);
    z = static_cast<T>(other.z);

    other.x = { };
    other.y = { };
    other.z = { };

    return *this;
}

template <typename T> template <typename U>
Vec<T, 3>& Vec<T, 3>::operator()(const Vec<U, 3>& other) noexcept { return (*this = other); }
template <typename T> template <typename U>
Vec<T, 3>& Vec<T, 3>::operator()(const U& _x) noexcept {
    x = static_cast<T>(_x);

    return *this;
}
template <typename T> template <typename U1, typename U2>
Vec<T, 3>& Vec<T, 3>::operator()(const U1& _x, const U2& _y) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);

    return *this;
}
template <typename T> template <typename U1, typename U2, typename U3>
Vec<T, 3>& Vec<T, 3>::operator()(const U1& _x, const U2& _y, const U3& _z) noexcept {
    x = static_cast<T>(_x);
    y = static_cast<T>(_y);
    z = static_cast<T>(_z);

    return *this;
}

template <typename T> T& Vec<T, 3>::operator[](const unsigned int& idx) {
    assert(idx < 3);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}
template <typename T> const T& Vec<T, 3>::operator[](const unsigned int& idx) const {
    assert(idx < 3);

    switch (idx) {
        default:
        case 0: return x;
        case 1: return y;
        case 2: return z;
    }
}

template <typename T> template <typename U>
inline constexpr T Vec<T, 3>::dot(const Vec<U, 3>& other) const noexcept {
    return static_cast<T>(
        x * other.x +
        y * other.y +
        z * other.z
    );
}
template <typename T> template <typename U>
inline Vec<T, 3> Vec<T, 3>::cross(const Vec<U, 3>& other) const noexcept {
    return {
        static_cast<T>(y * other.z - z * other.y),
        static_cast<T>(z * other.x - x * other.z),
        static_cast<T>(x * other.y - y * other.x)
    };
}

template <typename T> template <typename U>
inline constexpr T Vec<T, 3>::dot(const Vec<T, 3>& v1, const Vec<U, 3>& v2) noexcept { return v1.dot(v2); }
template <typename T> template <typename U>
inline Vec<T, 3> Vec<T, 3>::cross(const Vec<T, 3>& v1, const Vec<U, 3>& v2) noexcept { return v1.cross(v2); }