#pragma once

namespace TypeBase {
    struct trueType  { static constexpr bool value = true;  };
    struct falseType { static constexpr bool value = false; };


    template <typename T1, typename T2> struct isSame:       public falseType { };
    template <typename T>               struct isSame<T, T>: public trueType  { };


    template <typename T> struct removeReference      { using type = T; };
    template <typename T> struct removeReference<T&>  { using type = T; };
    template <typename T> struct removeReference<T&&> { using type = T; };


    template <typename T> struct isFloat:              public falseType { };
    template <>           struct isFloat<float>:       public trueType  { };
    template <>           struct isFloat<double>:      public trueType  { };
    template <>           struct isFloat<long double>: public trueType  { };

    template <typename T> struct isSignedInteger           : public falseType { };
    template <>           struct isSignedInteger<char>     : public trueType  { };
    template <>           struct isSignedInteger<short>    : public trueType  { };
    template <>           struct isSignedInteger<int>      : public trueType  { };
    template <>           struct isSignedInteger<long>     : public trueType  { };
    template <>           struct isSignedInteger<long long>: public trueType  { };

    template <typename T> struct isUnsignedInteger                    : public falseType { };
    template <>           struct isUnsignedInteger<unsigned char>     : public trueType  { };
    template <>           struct isUnsignedInteger<unsigned short>    : public trueType  { };
    template <>           struct isUnsignedInteger<unsigned int>      : public trueType  { };
    template <>           struct isUnsignedInteger<unsigned long>     : public trueType  { };
    template <>           struct isUnsignedInteger<unsigned long long>: public trueType  { };


    template <bool, typename, typename B> struct IF             { using type = B; };
    template <typename A, typename B>     struct IF<true, A, B> { using type = A; };

    template <bool, typename> struct enableIF          { };
    template <typename T>     struct enableIF<true, T> { using type = T; };
}

template <typename T1, typename T2>
inline constexpr bool isSame = TypeBase::isSame<T1, T2>::value;


template <typename T>
using removeReference = typename TypeBase::removeReference<T>::type;


template <typename T>
inline constexpr bool isFloat = TypeBase::isFloat<T>::value;
template <typename T>
inline constexpr bool isSignedInteger = TypeBase::isSignedInteger<T>::value;
template <typename T>
inline constexpr bool isUnsignedInteger = TypeBase::isUnsignedInteger<T>::value;
template <typename T>
inline constexpr bool isSigned = isSignedInteger<T> || isFloat<T>;
template <typename T>
inline constexpr bool isInteger = isSignedInteger<T> || isUnsignedInteger<T>;
template <typename T>
inline constexpr bool isArithmetic = isInteger<T> || isFloat<T>;


template <bool C, typename A, typename B>
using IF = typename TypeBase::IF<C, A, B>::type;

template <bool C, typename T = void>
using enableIF = typename TypeBase::enableIF<C, T>::type;


template <typename T>
[[nodiscard]] constexpr decltype(auto) move(T&& val) noexcept
{ return static_cast<removeReference<T>&&>(val); }