#pragma once

#include "../base.hpp"
#include "../typeHandler.hpp"
#include "../vector/vec3.hpp"
#include "../vector/vec4.hpp"

#include <cassert>      // assert()

template <typename T>
class Mat<T, 4, 4> {
    public:
        Mat() noexcept;
        Mat(const Mat<T, 4, 4>&) noexcept;
        Mat(Mat<T, 4, 4>&&) noexcept;
        ~Mat() noexcept;

        template <typename U>
        Mat(const Mat<U, 4, 4>&) noexcept;
        template <typename U>
        Mat(Mat<U, 4, 4>&&) noexcept;

        template <typename U1, typename U2, typename U3, typename U4>
        Mat(const Vec4<U1>&, const Vec4<U2>&, const Vec4<U3>&, const Vec4<U4>&) noexcept;

        Mat<T, 4, 4>& operator=(const Mat<T, 4, 4>&) noexcept;
        Mat<T, 4, 4>& operator=(Mat<T, 4, 4>&&) noexcept;

        template <typename U>
        Mat<T, 4, 4>& operator=(const Mat<U, 4, 4>&) noexcept;
        template <typename U>
        Mat<T, 4, 4>& operator=(Mat<U, 4, 4>&&) noexcept;

        template <typename U1, typename U2, typename U3, typename U4>
        Mat<T, 4, 4>& operator()(const Vec4<U1>&, const Vec4<U2>&, const Vec4<U3>&, const Vec4<U4>&) noexcept;

        Vec4<T>& operator[](const unsigned int& idx);
        const Vec4<T>& operator[](const unsigned int& idx) const;

        template <typename U> Mat<T, 4, 4>& operator+=(const Mat<U, 4, 4>&) noexcept;
        template <typename U> Mat<T, 4, 4>& operator-=(const Mat<U, 4, 4>&) noexcept;
        template <typename U> Mat<T, 4, 4>& operator*=(const Mat<U, 4, 4>&) noexcept;
        template <typename U> Mat<T, 4, 4>& operator*=(const U&) noexcept;
        template <typename U> Mat<T, 4, 4>& operator/=(const U&);

        template <typename U> inline Mat<T, 4, 4> operator+(const Mat<U, 4, 4>&) const noexcept;
        template <typename U> inline Mat<T, 4, 4> operator-(const Mat<U, 4, 4>&) const noexcept;
        template <typename U> inline Mat<T, 4, 4> operator*(const Mat<U, 4, 4>&) const noexcept;
        template <typename U> inline Mat<T, 4, 4> operator*(const U&) const noexcept;
        template <typename U> inline Mat<T, 4, 4> operator/(const U&) const;

        inline constexpr T trace() const noexcept;
        inline Mat<T, 4, 4> transpose() const noexcept;

        static inline constexpr T trace(const Mat<T, 4, 4>&) noexcept;
        static inline Mat<T, 4, 4> transpose(const Mat<T, 4, 4>&) noexcept;
        static inline Mat<T, 4, 4> identity() noexcept;

        static inline Mat<T, 4, 4> translate(const Vec3<T>&) noexcept;
        static inline Mat<T, 4, 4> scale(const Vec3<T>&) noexcept;

        template <typename U1, typename U2, typename U3>
        static inline Mat<T, 4, 4> translate(const U1&, const U2&, const U3&) noexcept;
        template <typename U>
        static inline Mat<T, 4, 4> scale(const U&) noexcept;

    public:
        Vec4<T> mROW[4];
};
template <typename T> using Mat4 = Mat<T, 4, 4>;

template <typename T> Mat<T, 4, 4>::Mat() noexcept { }
template <typename T> Mat<T, 4, 4>::Mat(const Mat<T, 4, 4>& other) noexcept { *this = other; }
template <typename T> Mat<T, 4, 4>::Mat(Mat<T, 4, 4>&& other) noexcept { *this = move(other); }
template <typename T> Mat<T, 4, 4>::~Mat() noexcept { }

template <typename T> template <typename U>
Mat<T, 4, 4>::Mat(const Mat<U, 4, 4>& other) noexcept { *this = other; }
template <typename T> template <typename U>
Mat<T, 4, 4>::Mat(Mat<U, 4, 4>&& other) noexcept { *this = move(other); }

template <typename T> template <typename U1, typename U2, typename U3, typename U4>
Mat<T, 4, 4>::Mat(const Vec4<U1>& v1, const Vec4<U2>& v2, const Vec4<U3>& v3, const Vec4<U4>& v4) noexcept { (*this)(v1, v2, v3, v4); }

template <typename T> Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(const Mat<T, 4, 4>& other) noexcept {
    mROW[0] = other.mROW[0];
    mROW[1] = other.mROW[1];
    mROW[2] = other.mROW[2];
    mROW[3] = other.mROW[3];

    return *this;
}
template <typename T> Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(Mat<T, 4, 4>&& other) noexcept {
    mROW[0] = other.mROW[0];
    mROW[1] = other.mROW[1];
    mROW[2] = other.mROW[2];
    mROW[3] = other.mROW[3];

    other.mROW[0] = { };
    other.mROW[1] = { };
    other.mROW[2] = { };
    other.mROW[3] = { };

    return *this;
}

template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(const Mat<U, 4, 4>& other) noexcept {
    mROW[0] = static_cast<Vec4<T>>(other.mROW[0]);
    mROW[1] = static_cast<Vec4<T>>(other.mROW[1]);
    mROW[2] = static_cast<Vec4<T>>(other.mROW[2]);
    mROW[3] = static_cast<Vec4<T>>(other.mROW[3]);

    return *this;
}
template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(Mat<U, 4, 4>&& other) noexcept {
    mROW[0] = static_cast<Vec4<T>>(other.mROW[0]);
    mROW[1] = static_cast<Vec4<T>>(other.mROW[1]);
    mROW[2] = static_cast<Vec4<T>>(other.mROW[2]);
    mROW[3] = static_cast<Vec4<T>>(other.mROW[3]);

    other.mROW[0] = { };
    other.mROW[1] = { };
    other.mROW[2] = { };
    other.mROW[3] = { };

    return *this;
}

template <typename T> template <typename U1, typename U2, typename U3, typename U4>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator()(const Vec4<U1>& v1, const Vec4<U2>& v2, const Vec4<U3>& v3, const Vec4<U4>& v4) noexcept {
    mROW[0] = v1;
    mROW[1] = v2;
    mROW[2] = v3;
    mROW[3] = v4;

    return *this;
}

template <typename T> Vec4<T>& Mat<T, 4, 4>::operator[](const unsigned int& idx) {
    assert(idx < 4);

    return mROW[idx];
}
template <typename T> const Vec4<T>& Mat<T, 4, 4>::operator[](const unsigned int& idx) const {
    assert(idx < 4);

    return mROW[idx];
}

template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator+=(const Mat<U, 4, 4>& other) noexcept {
    mROW[0] += other.mROW[0];
    mROW[1] += other.mROW[1];
    mROW[2] += other.mROW[2];
    mROW[3] += other.mROW[3];

    return *this;
}
template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator-=(const Mat<U, 4, 4>& other) noexcept {
    mROW[0] -= other.mROW[0];
    mROW[1] -= other.mROW[1];
    mROW[2] -= other.mROW[2];
    mROW[3] -= other.mROW[3];

    return *this;
}
template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator*=(const Mat<U, 4, 4>& other) noexcept { return (*this = ((*this) * other)); }
template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator*=(const U& val) noexcept {
    mROW[0] *= val;
    mROW[1] *= val;
    mROW[2] *= val;
    mROW[3] *= val;

    return *this;
}
template <typename T> template <typename U>
Mat<T, 4, 4>& Mat<T, 4, 4>::operator/=(const U& val) {
    mROW[0] /= val;
    mROW[1] /= val;
    mROW[2] /= val;
    mROW[3] /= val;

    return *this;
}

template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::operator+(const Mat<U, 4, 4>& other) const noexcept {
    return {
        mROW[0] + other.mROW[0],
        mROW[1] + other.mROW[1],
        mROW[2] + other.mROW[2],
        mROW[3] + other.mROW[3]
    };
}
template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::operator-(const Mat<U, 4, 4>& other) const noexcept {
    return {
        mROW[0] - other.mROW[0],
        mROW[1] - other.mROW[1],
        mROW[2] - other.mROW[2],
        mROW[3] - other.mROW[3]
    };
}
template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::operator*(const Mat<U, 4, 4>& other) const noexcept {
    Mat<T, 4, 4> result;

    T sum{ };
    for (unsigned int row = 0; row < 4; ++row) {
        for (unsigned int col = 0; col < 4; ++col) {
            for (unsigned int k = 0; k < 4; ++k)
                sum += static_cast<T>(mROW[row][k] * other.mROW[k][col]);

            result[row][col] = sum;
            sum = { };
        }
    }

    return result;
}
template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::operator*(const U& val) const noexcept {
    return {
        mROW[0] * val,
        mROW[1] * val,
        mROW[2] * val,
        mROW[3] * val
    };
}
template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::operator/(const U& val) const {
    return {
        mROW[0] / val,
        mROW[1] / val,
        mROW[2] / val,
        mROW[3] / val
    };
}

template <typename T> inline constexpr T Mat<T, 4, 4>::trace() const noexcept {
    return (
        mROW[0].x +
        mROW[1].y +
        mROW[2].z +
        mROW[3].w
    );
}
template <typename T> inline Mat<T, 4, 4> Mat<T, 4, 4>::transpose() const noexcept {
    Mat<T, 4, 4> m;

    for (unsigned int row = 0; row < 4; ++row) {
        for (unsigned int col = 0; col < 4; ++col)
            m[row][col] = mROW[col][row];
    }

    return m;
}

template <typename T> inline constexpr T Mat<T, 4, 4>::trace(const Mat<T, 4, 4>& m) noexcept { return m.trace(); }
template <typename T> inline Mat<T, 4, 4> Mat<T, 4, 4>::transpose(const Mat<T, 4, 4>& m) noexcept { return m.transpose(); }
template <typename T> inline Mat<T, 4, 4> Mat<T, 4, 4>::identity() noexcept {
    static constexpr T zero = static_cast<T>(0);
    static constexpr T one  = static_cast<T>(1);

    static const Mat4<T> i (
        Vec4<T>{  one, zero, zero, zero },
        Vec4<T>{ zero,  one, zero, zero },
        Vec4<T>{ zero, zero,  one, zero },
        Vec4<T>{ zero, zero, zero,  one }
    );

    return i;
}

template <typename T> inline Mat<T, 4, 4> Mat<T, 4, 4>::translate(const Vec3<T>& v) noexcept {
    Mat<T, 4, 4> t = Mat<T, 4, 4>::identity();

    t[0].w = v.x;
    t[1].w = v.y;
    t[2].w = v.z;

    return t;
}
template <typename T> inline Mat<T, 4, 4> Mat<T, 4, 4>::scale(const Vec3<T>& v) noexcept {
    Mat<T, 4, 4> s;

    v[0].x = v.x;
    v[1].y = v.y;
    v[2].z = v.z;
    v[3].w = static_cast<T>(1);

    return s;
}

template <typename T> template <typename U1, typename U2, typename U3>
inline Mat<T, 4, 4> Mat<T, 4, 4>::translate(const U1& x, const U2& y, const U3& z) noexcept { return Mat<T, 4, 4>::translate({x, y, z}); }
template <typename T> template <typename U>
inline Mat<T, 4, 4> Mat<T, 4, 4>::scale(const U& val) noexcept { return Mat<T, 4, 4>::scale({val, val, val}); }