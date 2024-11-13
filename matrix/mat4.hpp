#pragma once

#include "../base.hpp"
#include "../typeHandler.hpp"
#include "../vector/vec4.hpp"

template <typename T>
class Mat<T, 4, 4> {
    public:
        Mat();
        Mat(const Mat<T, 4, 4>&);
        Mat(Mat<T, 4, 4>&&) noexcept;
        ~Mat() noexcept;

        template <typename U>
        Mat(const Mat<U, 4, 4>&);
        template <typename U>
        Mat(Mat<U, 4, 4>&&) noexcept;

        Mat<T, 4, 4>& operator=(const Mat<T, 4, 4>&);
        Mat<T, 4, 4>& operator=(Mat<T, 4, 4>&&) noexcept;

        template <typename U>
        Mat<T, 4, 4>& operator=(const Mat<U, 4, 4>&);
        template <typename U>
        Mat<T, 4, 4>& operator=(Mat<U, 4, 4>&&) noexcept;

    public:
        Vec4<T> mROW[4];
};
template <typename T> using Mat4 = Mat<T, 4, 4>;

template <typename T> Mat<T, 4, 4>::Mat() { }
template <typename T> Mat<T, 4, 4>::Mat(const Mat<T, 4, 4>& other) { *this = other; }
template <typename T> Mat<T, 4, 4>::Mat(Mat<T, 4, 4>&& other) noexcept { *this = move(other); }
template <typename T> Mat<T, 4, 4>::~Mat() noexcept { }

template <typename T> template <typename U>
Mat<T, 4, 4>::Mat(const Mat<U, 4, 4>& other) { *this = other; }
template <typename T> template <typename U>
Mat<T, 4, 4>::Mat(Mat<U, 4, 4>&& other) noexcept { *this = move(other); }

template <typename T> Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(const Mat<T, 4, 4>& other) {
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
Mat<T, 4, 4>& Mat<T, 4, 4>::operator=(const Mat<U, 4, 4>& other) {
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

