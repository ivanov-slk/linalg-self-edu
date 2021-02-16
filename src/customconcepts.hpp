#pragma once
#include <concepts>

template <class T>
concept Integral = std::is_integral<T>::value;
template <class T>
concept SignedIntegral = Integral<T> &&std::is_signed<T>::value;
template <class T>
concept Number = SignedIntegral<T> || std::is_floating_point_v<T>;

// template <typename T, template <class> class R>
// concept MatrixRepresentation = Number<T> &&requires(R<T> x, R<T> y)
// {
//     {x.empty()};
//     {x.get_shape()};
//     {x.equals(y)};
// };

// template <Number T>
// class Matrix;

// template <typename T, template <class> class M>
// concept MatrixC = Number<T> &&requires(M<T>) { true; };

// template <class T, template <class> class D>
// concept Decomposer = Number<T> &&MatrixC<T, D> &&requires(D<T> d, Matrix<T> m)
// {
//     {
//         d(m)
//     }
//     ->MatrixC<T, Matrix<T>>;
// };