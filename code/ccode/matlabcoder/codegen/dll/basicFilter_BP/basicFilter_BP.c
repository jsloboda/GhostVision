/*
 * basicFilter_BP.c
 *
 * Code generation for function 'basicFilter_BP'
 *
 * C source code generated on: Sat Mar 29 00:00:50 2014
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "basicFilter_BP.h"
#include "ifft.h"
#include "fft.h"
#include "sum.h"

/* Function Definitions */
void basicFilter_BP(const real_T z[3664], real_T datf[3664])
{
  real_T H[4096];
  int32_T i;
  real_T y;
  real_T b_z[3664];
  static creal_T datK[4096];
  creal_T b_datK[4096];

  /* Filter3     Perform Low-pass filter on data */
  /* load('data_using_SD16_SPI.mat'); */
  /* z = data1; */
  /* Frequency domain filtering assumes kth-fft-point = (k-1)*Fs/N Hz; */
  /* Find N = fft size as a nearest integer power of 2 */
  /*  Np2 = nearest power of 2 */
  /* N = fft size */
  /* Implement BP Filter (with lower cut-off at LC Hz and upper cut-off at UC Hz) */
  /* input('Enter Lower Cut-off Frequency in Hz '); */
  /* input('Enter Upper Cut-off Frequency in Hz '); */
  memset(&H[0], 0, sizeof(real_T) << 12);
  for (i = 0; i < 68; i++) {
    H[i + 34] = 1.0;
  }

  for (i = 0; i < 68; i++) {
    H[i + 3994] = 1.0;
  }

  y = sum(z) / 3664.0;
  for (i = 0; i < 3664; i++) {
    b_z[i] = z[i] - y;
  }

  fft(b_z, datK);
  for (i = 0; i < 4096; i++) {
    b_datK[i].re = H[i] * datK[i].re;
    b_datK[i].im = H[i] * datK[i].im;
  }

  ifft(b_datK, datK);
  for (i = 0; i < 4096; i++) {
    H[i] = datK[i].re;
  }

  /* dataf = filtered data */
  memcpy(&datf[0], &H[0], 3664U * sizeof(real_T));

  /*  Plot results */
  /*  write to text file  */
  /* fileID = fopen('data1f.txt','w'); */
  /* fprintf(fileID,'%f \r\n',datf); */
  /* fclose(fileID); */
  /* data1f = datf; */
  /* save('data_point8to3.mat', 'data1f', 'data2f', 'data3f', 'data4f', 'data5f'); */
}

/* End of code generation (basicFilter_BP.c) */
