#define TYPEDEPARGS 0, 1
#define SINGLEARGS
#define COMPLEXARGS
#define OCTFILENAME comp_ifilterbank_fftbl // change to filename
#define OCTFILEHELP "This function calls the C-library\n c=upconv_fftbl(...);\n Yeah."


#include "ltfat_oct_template_helper.h"
// octave_idx_type 32 or 64 bit signed integer


static inline void
fwd_ifilterbank_fftbl(const Complex *c[], const Complex *G[],
                      const ltfatInt L, const ltfatInt Gl[],
                      const ltfatInt W, const double afrac[],
                      const ltfatInt M, const ltfatInt foff[],
                      const int realonly[], Complex *F)
{
    ifilterbank_fftbl_d(reinterpret_cast<const double _Complex **>(c),
                        reinterpret_cast<const double _Complex **>(G),
                        L,Gl,W,afrac,M,foff,realonly,
                        reinterpret_cast<double _Complex *>(F));
}

static inline void
fwd_ifilterbank_fftbl(const FloatComplex *c[], const FloatComplex *G[],
                      const ltfatInt L, const ltfatInt Gl[],
                      const ltfatInt W, const double afrac[],
                      const ltfatInt M, const ltfatInt foff[],
                      const int realonly[], FloatComplex *F)
{
    ifilterbank_fftbl_s(reinterpret_cast<const float _Complex **>(c),
                        reinterpret_cast<const float _Complex **>(G),
                        L,Gl,W,afrac,M,foff,realonly,
                        reinterpret_cast<float _Complex *>(F));
}


// Calling convention:
// F = comp_ifilterbank_fftbl(c,G,foff,a,realonly)
template <class LTFAT_TYPE, class LTFAT_REAL, class LTFAT_COMPLEX>
octave_value_list octFunction(const octave_value_list& args, int nargout)
{
    // Input data
    Cell c = args(0).cell_value();
    // Cell aray containing impulse responses
    Cell G = args(1).cell_value();
    // Subsampling factors
    Matrix foffDouble = args(2).matrix_value();
    const double* a = args(3).matrix_value().data();
    Matrix realonlyDouble = args(4).matrix_value();

    octave_idx_type acols = args(3).matrix_value().columns();
    // Number of channels
    const octave_idx_type W  = c.elem(0).columns();
    // Number of filters
    const octave_idx_type M = G.nelem();

    OCTAVE_LOCAL_BUFFER (double, afrac, M);
    memcpy(afrac,a,M*sizeof(double));
    if(acols>1)
    {
        for(octave_idx_type m=0; m<M; m++)
        {
            afrac[m]/=a[M+m];
        }
    }

    // Allocating
    // Output subband lengths
    OCTAVE_LOCAL_BUFFER (ltfatInt, foff, M);
    OCTAVE_LOCAL_BUFFER (ltfatInt, Gl, M);
    OCTAVE_LOCAL_BUFFER (int, realonly, M);
    // Impulse responses pointers
    OCTAVE_LOCAL_BUFFER (const LTFAT_COMPLEX*, GPtrs, M);
    // Output subbands pointers
    OCTAVE_LOCAL_BUFFER (const LTFAT_COMPLEX*, cPtrs, M);
    // Output cell elements array,
    OCTAVE_LOCAL_BUFFER (MArray<LTFAT_COMPLEX>, cElems, M);
    //
    OCTAVE_LOCAL_BUFFER (MArray<LTFAT_COMPLEX>, GElems, M);

    for(octave_idx_type m=0; m<M; m++)
    {
        realonly[m] = (realonlyDouble(m)>1e-3);
        foff[m] = foffDouble(m);
        GElems[m] = ltfatOctArray<LTFAT_COMPLEX>(G.elem(m));
        GPtrs[m] = GElems[m].data();
        cElems[m] = ltfatOctArray<LTFAT_COMPLEX>(c.elem(m));
        cPtrs[m] = cElems[m].data();
        Gl[m] = GElems[m].nelem();
    }

    // Output length
    octave_idx_type Lc = c.elem(0).rows();
    const octave_idx_type L  = floor(afrac[0]*Lc+0.5);
    // Output signal
    MArray<LTFAT_COMPLEX> F(dim_vector(L,W));

    fwd_ifilterbank_fftbl(cPtrs,GPtrs,L,Gl,W,afrac,M,
                          foff,realonly,F.fortran_vec());

    return octave_value(F);
}
