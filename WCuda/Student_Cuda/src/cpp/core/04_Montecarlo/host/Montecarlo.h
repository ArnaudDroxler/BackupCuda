#pragma once

#include "cudaTools.h"
#include "Grid.h"
#include <curand_kernel.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Montecarlo
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * update w by v1+v2
	 */
	Montecarlo(const Grid& grid, double* ptrResult, int nbDartsTotal, float m);

	virtual ~Montecarlo(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void run();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	dim3 dg;
	dim3 db;
	uint nbDartsTotal;
	float m;

	// Inputs/Outputs
	double* ptrResult;

	// Tools
	uint* ptrDevResult;
	curandState* ptrDevGenerators;

	size_t sizeOctetResultGM;
	size_t sizeOctetGeneratorsGM;
	size_t sizeOctetSM;


	uint nbDarts;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
