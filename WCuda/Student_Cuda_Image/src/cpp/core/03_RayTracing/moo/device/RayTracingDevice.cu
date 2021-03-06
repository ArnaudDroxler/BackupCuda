#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "IndiceTools_GPU.h"

#include "math/RayTracingMath.h"
#include "math/Sphere.h"
#include "length_cm.h"
using namespace gpu;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__host__ void uploadGPU(Sphere* tabSphere);

__global__ void rayTracingGM(Sphere* ptrDevTabSphere, uchar4* ptrDevPixels,uint w, uint h,float t);
__global__ void rayTracingCM(uchar4* ptrDevPixels,uint w, uint h,float t);
__global__ void rayTracingSM(Sphere* ptrDevTabSphere, uchar4* ptrDevPixels,uint w, uint h,float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void work (Sphere* ptrDevTabSphere,int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t);

__constant__ Sphere TAB_CM[LENGTH_CM];

__device__ void copyGMtoSM(Sphere* ptrDevTabSphere, Sphere* TAB_SM);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__host__ void uploadGPU(Sphere* tabSphere)
    {
    size_t size = LENGTH_CM * sizeof(Sphere);
    int offset = 0;
    HANDLE_ERROR(cudaMemcpyToSymbol(TAB_CM, tabSphere, size, offset, cudaMemcpyHostToDevice));
    }


__global__ void rayTracingGM(Sphere* ptrDevTabSphere, uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    work(ptrDevTabSphere, LENGTH_CM, ptrDevPixels, w, h, t);
    }

__global__ void rayTracingCM(uchar4* ptrDevPixels,uint w, uint h,float t)
    {
    work(TAB_CM, LENGTH_CM, ptrDevPixels, w, h, t);
    }


__global__ void rayTracingSM(Sphere* ptrDevTabSphere, uchar4* ptrDevPixels, uint w, uint h, float t)
    {
    extern __shared__ Sphere TAB_SM[];
    copyGMtoSM(ptrDevTabSphere, TAB_SM);
    __syncthreads();
    work(TAB_SM, LENGTH_CM, ptrDevPixels, w, h, t);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void copyGMtoSM(Sphere* ptrDevTabSphere, Sphere* TAB_SM)
    {
    const int TID_LOCAL = Indice2D::tidLocal();
    const int NB_THREAD_LOCAL = Indice2D::nbThreadLocal();

    int s = TID_LOCAL;

    while (s < LENGTH_CM)
	{
	TAB_SM[s] = ptrDevTabSphere[s];

	s+= NB_THREAD_LOCAL;
	}
    }

__device__ void work (Sphere* ptrDevTabSphere,int nbSphere, uchar4* ptrDevPixels, uint w, uint h, float t)
    {
	RayTracingMath rayTracingMath = RayTracingMath(nbSphere, ptrDevTabSphere);

        const int WH=w*h;
        const int TID = Indice2D::tid();
        const int NB_THREAD = Indice2D::nbThread();

        int i;
        int j;

        int s = TID;
        while (s < WH)
    	{
    	IndiceTools::toIJ(s, w, &i, &j);

    	rayTracingMath.colorIJ(&ptrDevPixels[s],i, j, t); 	// update ptrDevPixels[s]

    	s += NB_THREAD;
    	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

