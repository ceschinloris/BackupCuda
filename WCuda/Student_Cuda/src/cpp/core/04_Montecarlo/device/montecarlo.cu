#include "Indice1D.h"
#include "reductionADDLock.h"
#include <curand_kernel.h>


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(curandState* tabDevGeneratorGM, long nbDarts, long* ptrDevNxTotal);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x);
__device__ int mutex=0;
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* tabDevGeneratorGM, long nbDarts, uint m, long* ptrDevNxTotal)
    {
    extern __shared__ long TAB_SM[];

    //reductionIntraThread(TAB_SM, nbSlice);
    // lancer les flechettes
    // Regarder si elle est en dessous
    // ADD myNx


    const int NB_THREAD=Indice1D::nbThread();
    const int TID=Indice1D::tid();
    const int TIDLocal = Indice1D::tidLocal();

    curandState generator = tabDevGeneratorGM[TID];

    long localNx = 0;
    float x;
    float y;

    for(long i = 0; i < nbDarts; i++)
	{
	x = curand_uniform(&generator);
	// * M NORMALEMENT VVV
	y = curand_uniform(&generator) * m;

	if ( y  < f(x) )
	    {
	    localNx ++;
	    }
	}

    TAB_SM[TIDLocal] = localNx;

    __syncthreads();

    Lock l = Lock(&mutex);
    reductionADD<long>(TAB_SM, ptrDevNxTotal, &l);
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x)
    {
    return 4/(1+x*x);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

