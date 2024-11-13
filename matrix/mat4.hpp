#pragma once

#include "../base.hpp"
#include "../typeHandler.hpp"
#include "../vector/vec4.hpp"

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

        static inline Mat<T, 4, 4> identity() noexcept;

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