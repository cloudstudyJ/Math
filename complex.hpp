#pragma once

// inherit vector2D?
#include "./typeHandler.hpp"
#include "./math.hpp"

template <typename T>
class Complex {
    public:
        Complex();
        Complex(Complex<T>&& other) noexcept;
        Complex(const Complex<T>& other);
        Complex(const T& real, const T& imaginary);
        ~Complex() noexcept;

        Complex<T>& operator=(const Complex<T>& other);
        Complex<T>& operator=(Complex<T>&& other) noexcept;

        // comparing operators here
        // support floating-point types

        template <typename U> Complex<T>& operator+=(const Complex<U>& other) noexcept;
        template <typename U> Complex<T>& operator-=(const Complex<U>& other) noexcept;
        template <typename U> Complex<T>& operator*=(const Complex<U>& other) noexcept;
        template <typename U> Complex<T>& operator/=(const Complex<U>& other) noexcept;

        template <typename U> Complex<T> operator+(const Complex<U>& other) const noexcept;
        template <typename U> Complex<T> operator-(const Complex<U>& other) const noexcept;
        template <typename U> Complex<T> operator*(const Complex<U>& other) const noexcept;
        template <typename U> Complex<T> operator/(const Complex<U>& other) const noexcept;

        // add type restriction? (T must be signed)
        Complex<T> conjugate() const noexcept;

        void real(const T& real) noexcept;
        void imaginary(const T& imaginary) noexcept;

        inline T real() const noexcept;
        inline T imaginary() const noexcept;

    private:
        T mReal{ };
        T mImaginary{ };
};

template <typename T> Complex<T>::Complex() { }
template <typename T> Complex<T>::Complex(const T& real, const T& imaginary)
    : mReal{real}, mImaginary{imaginary} { }
template <typename T> Complex<T>::Complex(const Complex<T>& other) { *this = other; }
template <typename T> Complex<T>::Complex(Complex<T>&& other) noexcept { *this = move(other); }
template <typename T> Complex<T>::~Complex() noexcept { }

template <typename T> Complex<T>& Complex<T>::operator=(const Complex<T>& other) {
    mReal      = other.mReal;
    mImaginary = other.mImaginary;

    return *this;
}
template <typename T> Complex<T>& Complex<T>::operator=(Complex<T>&& other) noexcept {
    mReal      = other.mReal;
    mImaginary = other.mImaginary;

    other.mReal      = { };
    other.mImaginary = { };

    return *this;
}

template <typename T> template <typename U>
Complex<T>& Complex<T>::operator+=(const Complex<U>& other) noexcept { return (*this = (*this + other)); }
template <typename T> template <typename U>
Complex<T>& Complex<T>::operator-=(const Complex<U>& other) noexcept { return (*this = (*this - other)); }
template <typename T> template <typename U>
Complex<T>& Complex<T>::operator*=(const Complex<U>& other) noexcept { return (*this = (*this * other)); }
template <typename T> template <typename U>
Complex<T>& Complex<T>::operator/=(const Complex<U>& other) noexcept { return (*this = (*this / other)); }

template <typename T> template <typename U>
Complex<T> Complex<T>::operator+(const Complex<U>& other) const noexcept {
    // return Complex<decltype(mReal + other.real())>(real, imaginary);

    T real      = static_cast<T>(mReal + other.real());
    T imaginary = static_cast<T>(mImaginary + other.imaginary());

    return {real, imaginary};
}
template <typename T> template <typename U>
Complex<T> Complex<T>::operator-(const Complex<U>& other) const noexcept {
    T real      = static_cast<T>(mReal - other.real());
    T imaginary = static_cast<T>(mImaginary - other.imaginary());

    return {real, imaginary};
}
template <typename T> template <typename U>
Complex<T> Complex<T>::operator*(const Complex<U>& other) const noexcept {
    T real      = static_cast<T>(mReal * other.real() - mImaginary * other.imaginary());
    T imaginary = static_cast<T>(mReal * other.imaginary() + mImaginary * other.real());

    return {real, imaginary};
}
template <typename T> template <typename U>
Complex<T> Complex<T>::operator/(const Complex<U>& other) const noexcept {
    U denominator = Math::square(other.real()) + Math::square(other.imaginary());

    T      real = static_cast<T>((mReal * other.real() + mImaginary * other.imaginary()) / denominator);
    T imaginary = static_cast<T>((mImaginary * other.real() - mReal * other.imaginary()) / denominator);

    return {real, imaginary};
}

template <typename T> Complex<T> Complex<T>::conjugate() const noexcept { return Complex<T>(mReal, -mImaginary); }

template <typename T> void Complex<T>::real(const T& real) noexcept { mReal = real; }
template <typename T> void Complex<T>::imaginary(const T& imaginary) noexcept { mImaginary = imaginary; }

template <typename T> inline T Complex<T>::real() const noexcept { return mReal; }
template <typename T> inline T Complex<T>::imaginary() const noexcept { return mImaginary; }