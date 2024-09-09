#pragma once

#include "../utilities/typeHandler.hpp"

class Math {
    Math() = delete;
    Math(const Math&) = delete;
    Math(Math&&) noexcept = delete;
    ~Math() noexcept = delete;

    Math& operator=(const Math&) = delete;
    Math& operator=(Math&&) noexcept = delete;

    // numeric constants
    public:
        template <typename T>
        inline static constexpr T PI = static_cast<T>(3.141'592'653'589'793);

        template <typename T, typename = enableIF<isFloat<T>>>
        inline static constexpr T EPSILON = (isSame<T, float>) ? 1.0E-06f : 1.0E-15;

    // basic mathematics functions
    public:
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T abs(const T& val) noexcept;
        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr T square(const T& val) noexcept;

        template <typename T, typename = enableIF<isArithmetic<T>>>
        inline static constexpr bool isZero(const T& val) noexcept;
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
inline constexpr bool Math::isZero(const T& val) noexcept {
    if constexpr (isFloat<T>)
        return (Math::abs(val) <= EPSILON<T>);

    return (val == 0);
}