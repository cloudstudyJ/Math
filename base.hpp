#pragma once

#include "typeHandler.hpp"

template <typename T, unsigned int DIM, typename = enableIF<isArithmetic<T>>>
class Vec;

template <typename T, unsigned int ROW, unsigned int COL, typename = enableIF<isArithmetic<T>>>
class Mat;