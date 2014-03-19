#define TYPEDEPARGS 0
#define SINGLEARGS
#define COMPLEXINDEPENDENT
#define OCTFILENAME comp_chirpzt // change to filename
#define OCTFILEHELP "This function calls the C-library\n c=chzt(...);\n Yeah."

#include "ltfat_oct_template_helper.h"
// octave_idx_type 32 or 64 bit signed integer

static inline void
fwd_chzt(const Complex *fPtr, const octave_idx_type L, const octave_idx_type W,
         const octave_idx_type K, const double deltao, const double o, Complex *cPtr )
{
   chzt_cd(reinterpret_cast<const double _Complex *>(fPtr),
           L,W,K,deltao,o,
           reinterpret_cast<double _Complex *>(cPtr));
}

static inline void 
fwd_chzt(const FloatComplex *fPtr, const octave_idx_type L, const octave_idx_type W,
         const octave_idx_type K, const double deltao, const double o, FloatComplex *cPtr )
{
   chzt_cs(reinterpret_cast<const float _Complex *>(fPtr),
           L,W,K,deltao,o,
           reinterpret_cast<float _Complex *>(cPtr));
}

static inline void 
fwd_chzt(const double *fPtr, const octave_idx_type L, const octave_idx_type W,
         const octave_idx_type K, const double deltao, const double o, Complex *cPtr )
{
   chzt_d(fPtr,L,W,K,deltao,o,reinterpret_cast<double _Complex *>(cPtr));
}

static inline void 
fwd_chzt(const float *fPtr,const octave_idx_type L, const octave_idx_type W,
         const octave_idx_type K, const double deltao, const double o, FloatComplex *cPtr )
{
   chzt_s(fPtr, L,W,K,deltao,o,reinterpret_cast<float _Complex *>(cPtr));
}

template <class LTFAT_TYPE, class LTFAT_REAL, class LTFAT_COMPLEX>
octave_value_list
octFunction(const octave_value_list& args, int nargout)
{
   //DEBUGINFO;
   // Input data
   MArray<LTFAT_TYPE> f = ltfatOctArray<LTFAT_TYPE>(args(0));
   const octave_idx_type K = (octave_idx_type) args(1).double_value();
   const double deltao = args(2).double_value();
   const double o = args(3).double_value();
   
  // Input length
   const octave_idx_type L  = f.rows();
   // Number of channels
   const octave_idx_type W  = f.columns();

   //dims_out.chop_trailing_singletons();
   MArray<LTFAT_COMPLEX> c(dim_vector(K,W));
   
   fwd_chzt(f.data(),L,W,K,deltao,o,c.fortran_vec());
   
   return octave_value(c);
}
