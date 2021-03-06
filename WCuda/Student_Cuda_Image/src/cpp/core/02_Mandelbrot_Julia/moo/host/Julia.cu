#include "Julia.h"

#include <iostream>
#include <assert.h>

#include "Device.h"
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void julia(float c1, float c2, uchar4* ptrDevPixels, uint w, uint h, float t, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Julia::Julia(float c1, float c2, uint nMin, uint nMax, const Grid& grid, uint w, uint h, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Julia_Cuda_RGBA_uchar4", domaineMath), variateurAnimation(Interval<float>(nMin, nMax), 1.f)
    {
    // Inputs
    this->c1 = c1;
    this->c2 = c2;

    // Tools
    this->t = nMin; // protected dans Animable
    }

Julia::~Julia()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Julia::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    t = variateurAnimation.get();
    julia <<<dg,db>>>(c1, c2, ptrDevPixels, w, h, t, domaineMath);

    }

/**
 * Override
 * Call periodicly by the API
 */
void Julia::animationStep()
    {
    t = variateurAnimation.varierAndGet();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

