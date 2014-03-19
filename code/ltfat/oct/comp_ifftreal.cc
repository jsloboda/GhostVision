#define TYPEDEPARGS 0
#define SINGLEARGS
#define COMPLEXARGS
#define OCTFILENAME comp_ifftreal // change to filename
#define OCTFILEHELP "This function calls the FFTW3 real FFT\n\
                    f=comp_ifftreal(c,L2);\n\
                    Yeah."


#include "ltfat_oct_template_helper.h"
#include "config.h"
#include "fftw3.h"
// octave_idx_type is 32 or 64 bit signed integer

static inline void fwd_ifftreal(const Complex *c,
                                const octave_idx_type L,
                                const octave_idx_type W,
                                double *f)
{
  ifftreal_d(const_cast<double _Complex*>(reinterpret_cast<const double _Complex*>(c)),
           L,W,f);
}

static inline void fwd_ifftreal(const FloatComplex *c,
                                const octave_idx_type L,
                                const octave_idx_type W,
                                float *f)
{
   ifftreal_s(const_cast<float _Complex*>(reinterpret_cast<const float _Complex*>(c)),
           L,W,f);
}

template <class LTFAT_TYPE, class LTFAT_REAL, class LTFAT_COMPLEX>
octave_value_list octFunction(const octave_value_list& args, int nargout)
{
     MArray<LTFAT_TYPE> c = ltfatOctArray<LTFAT_TYPE>(args(0));
  
     const octave_idx_type W  = c.columns();
     const octave_idx_type L = args(1).int_value();
  
     MArray<LTFAT_REAL> f(dim_vector(L,W)); 
         
     fwd_ifftreal(c.data(),L,W,f.fortran_vec());
         
     return octave_value(f);
}

