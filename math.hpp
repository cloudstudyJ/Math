#pragma once

#include "./base.hpp"

// log2, log, ln, pow, exp
// support raw array type to min(), max()

class Math {
    // Numeric Constants
    public:
        template <typename T>
        inline static constexpr T PI = static_cast<T>(3.141'592'653'589'793);

        template <typename T, typename = enableIF<isFloat<T>>>
        inline static constexpr T EPSILON = (isSame<T, float>) ? 1.0E-06f : 1.0E-15;

    // Base Functions
    public:
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T abs(const T&) noexcept;

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T square(const T&) noexcept;
        template <typename T, unsigned int ROW, unsigned int COL>
        inline static constexpr Mat<T, ROW, COL> square(const Mat<T, ROW, COL>&) noexcept;

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static float sqrtf(const T&) noexcept;

        // conversions
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T toRad(const T&) noexcept;
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T toDeg(const T&) noexcept;

        // support raw array
        template <typename T, typename U, typename ...TYPES>
        inline static constexpr decltype(auto) min(T&&, U&&, TYPES&&...);
        template <typename T, typename U, typename ...TYPES>
        inline static constexpr decltype(auto) max(T&&, U&&, TYPES&&...);

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr bool isZero(const T&) noexcept;
        template <typename T, unsigned int DIM>
        inline static constexpr bool isZero(const Vec<T, DIM>&) noexcept;
        template <typename T, unsigned int ROW, unsigned int COL>
        inline static constexpr bool isZero(const Mat<T, ROW, COL>&) noexcept;

    private:
        // determination of the last recursive call's return value (= returns min value or max value)
        template <typename T> inline static constexpr decltype(auto) min(T&&) noexcept;
        template <typename T> inline static constexpr decltype(auto) max(T&&) noexcept;
};

template <typename T, typename>
inline constexpr T Math::abs(const T& val) noexcept {
    if constexpr (isFloat<T>) {
        using iType = IF<isSame<T, float>, unsigned int, unsigned long long>;

        union {
            T     f;
            iType i;
        } conv;

        conv.f  = val;
        conv.i &= (isSame<T, float>) ? 0x7FFF'FFFF : 0x7FFF'FFFF'FFFF'FFFF;

        return conv.f;
    }
    else if (isSignedInteger<T>)
        return (val < 0) ? -val : val;

    // unsigned integers
    return val;
}

template <typename T, typename>
inline constexpr T Math::square(const T& val) noexcept { return val * val; }
template <typename T, unsigned int ROW, unsigned int COL>
inline constexpr Mat<T, ROW, COL> Math::square(const Mat<T, ROW, COL>& mat) noexcept {
    static_assert(ROW == COL, "can not define matrix multiplication");

    return { mat * mat };
}

template <typename T, typename>
inline float Math::sqrtf(const T& val) noexcept {
    // https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi

    union {
        float f;
        int   i;
    } conv;

    conv.f = static_cast<float>(val);
    conv.i = (1 << 29) + (conv.i >> 1) - (1 << 22);

    conv.f = conv.f + static_cast<float>(val / conv.f);
    conv.f = 0.25f * conv.f + static_cast<float>(val / conv.f);

    return conv.f;
}

template <typename T, typename>
inline constexpr T Math::toRad(const T& deg) noexcept { return static_cast<T>((PI<double> / 180) * deg); }
template <typename T, typename>
inline constexpr T Math::toDeg(const T& rad) noexcept { return static_cast<T>((180 / PI<double>) * rad); }

template <typename T, typename U, typename... TYPES>
inline constexpr decltype(auto) Math::min(T&& a, U&& b, TYPES&&... args) {
    static_assert(isArithmetic<T>, "template type T is not an arithmetic type");
    static_assert(isArithmetic<U>, "template type U is not an arithmetic type");

    return min((a < b ? a : b), args...);
}
template <typename T, typename U, typename... TYPES>
inline constexpr decltype(auto) Math::max(T&& a, U&& b, TYPES&&... args) {
    static_assert(isArithmetic<T>, "template type T is not an arithmetic type");
    static_assert(isArithmetic<U>, "template type U is not an arithmetic type");

    return max((a > b ? a : b), args...);
}

template <typename T, typename>
inline constexpr bool Math::isZero(const T& val) noexcept {
    if constexpr (isFloat<T>)
        return (Math::abs(val) <= EPSILON<T>);

    return (val == 0);
}
template <typename T, unsigned int DIM>
inline constexpr bool Math::isZero(const Vec<T, DIM>& vec) noexcept {
    for (unsigned int i = 0; i < DIM; ++i) {
        if (!isZero(vec[i]))
            return false;
    }

    return true;
}
template <typename T, unsigned int ROW, unsigned int COL>
inline constexpr bool Math::isZero(const Mat<T, ROW, COL>& mat) noexcept {
    for (unsigned int row = 0; row < ROW; ++row) {
        for (unsigned int col = 0; col < COL; ++col) {
            if (!isZero(mat[row][col]))
                return false;
        }
    }

    return true;
}

template <typename T> inline constexpr decltype(auto) Math::min(T&& val) noexcept { return val; }
template <typename T> inline constexpr decltype(auto) Math::max(T&& val) noexcept { return val; }