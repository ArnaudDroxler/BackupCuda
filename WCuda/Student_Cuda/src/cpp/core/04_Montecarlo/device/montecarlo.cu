#include "Indice1D.h"
#include "reductionADD.h"
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

__global__ void montecarlo(curandState* tabDevGeneratorGM, uint nbDarts, uint* ptrDevNxTotal);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* tabDevGeneratorGM, uint nbDarts, uint* ptrDevNxTotal)
    {
    extern __shared__ uint TAB_SM[];

    //reductionIntraThread(TAB_SM, nbSlice);
    // lancer les flechettes
    // Regarder si elle est en dessous
    // ADD myNx


    const int NB_THREAD=Indice1D::nbThread();
    const int TID=Indice1D::tid();
    const int TIDLocal = Indice1D::tidLocal();

    curandState generator = tabDevGeneratorGM[TID];

    int localNx = 0;
    float x;
    float y;

    for(int i = 0; i < nbDarts; i++)
	{
	x = curand_uniform(&generator);
	// * M NORMALEMENT VVV
	y = curand_uniform(&generator) * 10;

	if ( y  < f(x) )
	    {
	    localNx ++;
	    }
	}

    TAB_SM[TIDLocal] = localNx;

    __syncthreads();

    reductionADD<uint>(TAB_SM, ptrDevNxTotal);
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
