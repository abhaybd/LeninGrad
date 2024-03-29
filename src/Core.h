#pragma once

#include "Derivative.h"
#include "DiffArithmetic.h"
#include "DiffComparison.h"
#include "DiffOps.h"
#include "DiffValue.h"

namespace leningrad {
using ddouble = DiffValue<double>;
using dfloat = DiffValue<float>;
} // namespace leningrad
