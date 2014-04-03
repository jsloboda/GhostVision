#ifndef __MATRICES_H__
#define __MATRICES_H__

#include <cstddef>
#include <map>
#include <complex>

class Matrix
{
	public:
		/* Constructor(s)/destructor. */
		Matrix();								/* Uninitialized matrix. */
		Matrix( std::complex <double> *data, size_t numberOfColumns, size_t numberOfRows );		/* Initialize the matrix. */
		Matrix( double *data, size_t numberOfColumns, size_t numberOfRows );		/* Initialize the matrix. */
		virtual ~Matrix();

		/* Data insertion and removal methods. */
		/* Data addition: */
		int addRow( double *data, size_t size );					/* Add row of double. */
		int addRow( std::complex<double> *data, size_t size );				/* Add row of complex. */
		int addColumn( double *data, size_t size );					/* Add column of double. */
		int addColumn( std::complex<double> *data, size_t size );				/* Add column of complex. */
		/* Data insertion: */
		int insertRow( double *data, size_t size, size_t position );			/* Insert row of double. */;
		int insertRow( std::complex<double> *data, size_t size, size_t position );		/* Insert row of complex. */
		int insertColumn( double *data, size_t size, size_t position );			/* Insert column of double. */
		int insertColumn( std::complex<double> *data, size_t size, size_t position );	/* Insert column of complex. */
		/* Data Removal: */
		int delRow( size_t );								/* Delete row. */
		int delColumn( size_t );							/* Delete column. */

		/* Arithmatic operators. */
		Matrix operator= ( Matrix );
		Matrix operator= ( std::complex<double> );
		Matrix operator= ( double );
		Matrix operator+ ( Matrix );
		Matrix operator+ ( std::complex<double> );
		Matrix operator+ ( double );
		Matrix operator- ( Matrix );
		Matrix operator- ( std::complex<double> );
		Matrix operator- ( double );
		Matrix operator* ( Matrix );
		Matrix operator* ( std::complex<double> );
		Matrix operator* ( double );
		Matrix operator/ ( Matrix );
		Matrix operator/ ( std::complex<double> );
		Matrix operator/ ( double );

		template< typename T >
		Matrix operator+= ( T x ) { return *this = *this + x; }
		template< typename T >
		Matrix operator-= ( T x ) { return *this = *this - x; }
		template< typename T >
		Matrix operator*= ( T x ) { return *this = *this * x; }
		template< typename T >
		Matrix operator/= ( T x ) { return *this = *this / x; }

		/* Logic operations. */
		Matrix operator== ( Matrix );
		Matrix operator== ( std::complex<double> );
		Matrix operator== ( double );
		Matrix operator!= ( Matrix );
		Matrix operator!= ( std::complex<double> );
		Matrix operator!= ( double );
		Matrix operator> ( Matrix );
		Matrix operator> ( std::complex<double> );
		Matrix operator> ( double );
		Matrix operator< ( Matrix );
		Matrix operator< ( std::complex<double> );
		Matrix operator< ( double );
		Matrix operator>= ( Matrix );
		Matrix operator>= ( std::complex<double> );
		Matrix operator>= ( double );
		Matrix operator<= ( Matrix );
		Matrix operator<= ( std::complex<double> );
		Matrix operator<= ( double );

		Matrix operator| ( Matrix );
		Matrix operator| ( double );
		Matrix operator& ( Matrix );
		Matrix operator& ( double );

		Matrix operator! ();

		/* Matrix operations. */
		Matrix inverse();
		Matrix transpose();
		Matrix cofactors();
		std::complex<double> determinant();

		/* Element manipulation. */
		int getElement( std::complex <double> *, size_t col, size_t row);
		int getElement( std::complex <double> *, size_t );
		int getElement( double *, size_t col, size_t row);
		int getElement( double *, size_t );
		int setElement( std::complex <double>, size_t col, size_t row);
		int setElement( double, size_t col, size_t row);
		int setElement( std::complex <double>, size_t );
		int setElement( double, size_t );
		Matrix getSubMatrix( size_t start_col, size_t end_col, size_t start_row, size_t end_row );
		std::complex <double> * getRow( size_t row );
		std::complex <double> * getColumn( size_t column );

		/* Miscellaneous. */
		void size( size_t *, size_t* );
		bool isempty();
		bool isvector();
		bool isreal();
		void printout();
		void clear();
		Matrix reshape( size_t, size_t );
		
	private:
		bool initialized;
		size_t Ncolumns;
		size_t Nrows;
		std::map< size_t, std::map< size_t, std::complex<double> > > data;

};



/* Arithmatic functions. */
Matrix dotProduct( Matrix, Matrix );
Matrix dotProduct( Matrix, std::complex<double> );
Matrix dotProduct( Matrix, double );
Matrix dotProduct( std::complex<double>, Matrix );
Matrix dotProduct( double, Matrix );
Matrix dotDivision( Matrix, Matrix );
Matrix dotDivision( Matrix, std::complex<double> );
Matrix dotDivision( Matrix, double );
Matrix dotDivision( std::complex<double>, Matrix );
Matrix dotDivision( double, Matrix );

/* Matlab: exp(). */
Matrix exp( Matrix );

/* Matlab: round(). */
Matrix round( Matrix );

/* Matlab: max(). */
Matrix max( Matrix, Matrix );
Matrix max( Matrix );
Matrix max( Matrix, double );
double max( double, double );

/* Matlab: min(). */
Matrix min( Matrix, Matrix );
Matrix min( Matrix );
Matrix min( Matrix, double );
double min( double, double );

/* Matlab: repmat(). */
Matrix repmat( Matrix, size_t n );
Matrix repmat( Matrix, size_t y, size_t x );

/* Matlab: length(). */
size_t length( Matrix );

/* Matlab: size(). */
Matrix size( Matrix );
size_t size( Matrix, size_t dim );

/* Matlab: sum(). */
Matrix sum( Matrix );
Matrix sum( Matrix, size_t );

/* Matlab: mean(). */
Matrix mean( Matrix );
Matrix mean( Matrix, size_t );

/* Matlab: sqrt(). */
Matrix sqrt( Matrix );

/* Matlab: find(). */
Matrix find( Matrix );

/* Matlab: mpower(). */
Matrix mpower( Matrix, double );

/* Matlab: power() || .^ */
Matrix power( Matrix, Matrix );
Matrix power( Matrix, double );
Matrix power( Matrix, std::complex<double> );
Matrix power( double, Matrix );
Matrix power( std::complex<double>, Matrix );

/* Matlab: pow2(). */
Matrix pow2( Matrix );

/* Matlab: nextpow2. */
Matrix nextpow2( Matrix );
double nextpow2( double );

/* Matlab: conj(). */
Matrix conj( Matrix );

/* Matlab: real(). */
Matrix real( Matrix );

/* Matlab: imag(). */
Matrix imag( Matrix );

/* Matlab: abs(). */
Matrix abs( Matrix );

/* Matlab: tan(). */
Matrix tan( Matrix );

/* Matlab: cos(). */
Matrix cos( Matrix );

/* Matlab: sin(). */
Matrix sin( Matrix );

/* Matlab: atan2(). */
Matrix atan2( Matrix, Matrix );
Matrix atan2( std::complex<double>, Matrix );
Matrix atan2( Matrix, std::complex<double> );
std::complex<double> atan2( std::complex<double>, std::complex<double> );

/* Matlab: log10(). */
Matrix log10( Matrix );

/* Matlab: floor(). */
Matrix floor( Matrix );

/* Matlab: ceil(). */
Matrix ceil( Matrix );

/* Matlab: log2(). */
Matrix log2( Matrix );
std::complex <double> log2( std::complex <double> );
double log2( double );

/* Creating a matrix of ones. */
Matrix ones( size_t );
Matrix ones( size_t, size_t );

/* Creating a matrix of zeros. */
Matrix zeros( size_t );
Matrix zeros( size_t, size_t );

/* Creating an identity matrix. */
Matrix eye( size_t );
Matrix eye( size_t, size_t );

/* Creating a random (normal distribution) matrix. */
Matrix randn( size_t );
Matrix randn( size_t, size_t );

/* matlab: hamming(). */
Matrix hamming( size_t );

/* matlab: hanning(). */
Matrix hanning( size_t );

/* matlab: hann(). */
Matrix hann( size_t );

/* matlab: reshape(). */
Matrix reshape( Matrix, size_t, size_t );

/* matlab: flipud(). */
Matrix flipud( Matrix );

/* matlab: fft(). */
Matrix fft( Matrix );
Matrix fft( Matrix, size_t );
Matrix fft( Matrix, size_t, size_t );

/* matlab: fft(). */
Matrix ifft( Matrix );
Matrix ifft( Matrix, size_t );
Matrix ifft( Matrix, size_t, size_t );

/* matlab:conv() */
Matrix conv( Matrix, Matrix );

/* replacing matlab's (start:end). */
Matrix seq( double start, double end );

/* replacing matlab's (start:step:end). */
Matrix seq( double start, double step, double end );

/* matlab: cat(). */
Matrix cat( size_t dim, Matrix mata, Matrix matb );

/* Fix functions. */
double fix( double val );
std::complex<double> fix( std::complex<double> val );
Matrix fix( Matrix mat );

/* matlab: any() */
bool any( Matrix );

/* matlab: rem() */
double rem( double val1, double val2 );
Matrix rem( Matrix mat, double val );
Matrix rem( double val, Matrix mat );
Matrix rem( Matrix mat1, Matrix mat2 );

/* Matlab: filter(). */
Matrix filter( Matrix b, Matrix a, Matrix x );

/* Matlab: toeplitz(). */
Matrix toeplitz( Matrix );
Matrix toeplitz( Matrix col, Matrix row );

/* Matlab: xcorr(). */
Matrix xcorr( Matrix );

/* Matlab: lu(). */
void lu( Matrix a, Matrix *l, Matrix *u, Matrix *p );

#endif //__MATRICES_H__
