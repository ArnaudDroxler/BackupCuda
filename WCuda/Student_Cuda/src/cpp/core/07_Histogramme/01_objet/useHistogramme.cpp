#include <iostream>
#include "Grid.h"
#include "Device.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "Histogramme.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHistogramme(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHistogramme()
    {
    int dataMax = 255;

    int result[dataMax];

    // Grid cuda
    int mp = Device::getMPCount();

    dim3 dg = dim3(mp, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db = dim3(64, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    Grid grid(dg, db);

    Histogramme histogramme(grid, result, dataMax);
    histogramme.run();

    for (int i = 0; i < dataMax; i++ ) {
          printf("Element[%d] = %d\n", i, result[i] );
       }




    bool isOk = true;


    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

