#pragma once

#include "./base.hpp"

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

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr double toRad(const T&) noexcept;
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr double toDeg(const T&) noexcept;

        template <typename T, typename U, typename ...TYPES>
        inline static constexpr decltype(auto) min(T&&, U&&, TYPES&&...);
        template <typename T, typename U, typename ...TYPES>
        inline static constexpr decltype(auto) max(T&&, U&&, TYPES&&...);

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr bool isZero(const T&);

    private:
        // determination of the last recursive call's return value (= returns min value or max value)
        template <typename T> inline static constexpr decltype(auto) min(T&&) noexcept;
        template <typename T> inline static constexpr decltype(auto) max(T&&) noexcept;
};

template <typename T, typename>
inline constexpr T Math::abs(const T& val) noexcept {
    if constexpr (isFloat<T>) {
        using iType = IF<isSame<T, float>, unsigned int, unsigned long long>;

        union converter {
                T f;
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
inline constexpr double Math::toRad(const T& deg) noexcept { return (PI<double> / 180) * deg; }
template <typename T, typename>
inline constexpr double Math::toDeg(const T& rad) noexcept { return (180 / PI<double>) * rad; }

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
inline constexpr bool Math::isZero(const T& val) {
    if constexpr (isFloat<T>)
        return (Math::abs(val) <= EPSILON<T>);

    return (val == 0);
}


template <typename T> inline constexpr decltype(auto) Math::min(T&& val) noexcept { return val; }
template <typename T> inline constexpr decltype(auto) Math::max(T&& val) noexcept { return val; }