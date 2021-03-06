#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_CPU.h"

#include "FractaleMath.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotV2Math : public FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotV2Math(uint n) :
		FractaleMath(n)
	    {
	    }

	~MandelbrotV2Math()
	    {
	    //Rien
	    }


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    private:

	virtual int f(float x, float y, float t)
	    {
	    float a = 0;
	    float b = 0;
	    float aCopy = 0;

	    for(int i = 0; i < t; i++)
		{
		aCopy = a;
		a = (a*a - b*b) + x;
		b = 2 * aCopy * b + y;

		if(isStop(a, b))
		    return i;
		}
	    return t;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/


    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
