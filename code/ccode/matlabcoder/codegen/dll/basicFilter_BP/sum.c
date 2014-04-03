/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Sat Mar 29 00:00:50 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "basicFilter_BP.h"
#include "sum.h"

/* Function Definitions */
real_T sum(const real_T x[3664])
{
  real_T y;
  int32_T k;
  y = x[0];
  for (k = 0; k < 3663; k++) {
    y += x[k + 1];
  }

  return y;
}

/* End of code generation (sum.c) */
