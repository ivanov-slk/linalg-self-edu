#pragma once
#include <concepts>
#include "../customconcepts.hpp"

template <class T>
concept MatrixRepresentation =
    requires(T x)
{
    typename T::data;
    x.add();
};
