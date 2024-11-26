#pragma once

#include "base.hpp"

class Math {
    Math() = delete;
    Math(const Math&) = delete;
    Math(Math&&) noexcept = delete;
    ~Math() noexcept = delete;

    Math& operator=(const Math&) = delete;
    Math& operator=(Math&&) noexcept = delete;

    // Numeric Constants
    public:
        template <typename T> inline static constexpr T PI = static_cast<T>(3.141'592'653'589'793);
        template <typename T> inline static constexpr T E  = static_cast<T>(2.718'281'828'459'045);

        template <typename T, typename = enableIF<isFloat<T>>>
        inline static constexpr T EPSILON = (isSame<T, float>) ? 1.0E-06f : 1.0E-15;

    public:
        // Basic Functions
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T abs(const T&) noexcept;
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T square(const T&) noexcept;

        // Conversions
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T toRad(const T&) noexcept;
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T toDeg(const T&) noexcept;

        // Booleans
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr bool isZero(const T&) noexcept;
        template <typename T, unsigned int DIM>
        inline static constexpr bool isZero(const Vec<T, DIM>&) noexcept;

        // Interpolations
        template <typename T1, typename T2, unsigned int DIM>
        inline static constexpr Vec<float, DIM> lerpf(const Vec<T1, DIM>&, const Vec<T2, DIM>&, const float&) noexcept;
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

template <typename T, typename>
inline constexpr T Math::toRad(const T& deg) noexcept { return static_cast<T>((PI<double> / 180) * deg); }
template <typename T, typename>
inline constexpr T Math::toDeg(const T& rad) noexcept { return static_cast<T>((180 / PI<double>) * rad); }

template <typename T, typename>
inline constexpr bool Math::isZero(const T& val) noexcept {
    if constexpr (isFloat<T>)
        return (Math::abs(val) <= EPSILON<T>);

    return (val == 0);
}
template <typename T, unsigned int DIM>
inline constexpr bool Math::isZero(const Vec<T, DIM>& v) noexcept {
    for (unsigned int i = 0; i < DIM; ++i) {
        if (!isZero(v[i]))
            return false;
    }

    return true;
}
template <typename T1, typename T2, unsigned int DIM>
inline constexpr Vec<float, DIM> Math::lerpf(const Vec<T1, DIM>& v1, const Vec<T2, DIM>& v2, const float& t) noexcept { return { (v1 * (1.0f - t)) + (v2 * t) }; }