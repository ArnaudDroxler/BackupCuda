
#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SliceTools
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__ static float fpi(float x)
	    {
	    return 4.0f / (1.0f + x * x);
	    }

    private:



	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/