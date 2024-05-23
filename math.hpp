#pragma once

class Math {
    public:
        template <typename T>
        static inline constexpr T square(const T& val);
};

template <typename T>
inline constexpr T Math::square(const T& val) { return val * val; }