#pragma once
#include <concepts>

template <class T>
concept Integral = std::is_integral<T>::value;
template <class T>
concept SignedIntegral = Integral<T> &&std::is_signed<T>::value;
template <class T>
concept Number = SignedIntegral<T> || std::is_floating_point_v<T>;

template <class R>
concept MatrixRepresentation = requires(R x)
{
    {x.empty()};
    // ->std::same_as<bool>;
};
