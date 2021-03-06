#include "JuliaProvider.h"

#include "Julia.h"

#include "MathTools.h"
#include "Grid.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

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

/**
 * Override
 */
Animable_I<uchar4>* JuliaProvider::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-1.3,-1.4,1.3,1.4);

    // Parametre de Julia
    float c1 = -0.12;
    float c2 = 0.85;

    // Animation;
    int nMin = 10;
    int nMax = 100;

    // Dimension
    int dw = 16 * 80;
    int dh = 16 * 60;

    // Grid Cuda
    int mp=Device::getMPCount();
    int coreMP=Device::getCoreCountMP();

    dim3 dg = dim3(mp, 2, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db = dim3(coreMP, 2, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    return new Julia(c1, c2, nMin, nMax, grid, dw, dh, domaineMath);
    }

/**
 * Override
 */
Image_I* JuliaProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
