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

class JuliaMath : public FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	JuliaMath(uint n, float c1, float c2) :
		FractaleMath(n)
	    {
	    this->c1 = c1;
	    this->c2 = c2;
	    }

	~JuliaMath()
	    {
	    //Rien
	    }


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    private:

	virtual int f(float x, float y, float t)
	    {
	    float a = x;
	    float b = y;
	    float aCopy = 0;

	    for(int i = 0; i < t; i++)
		{
		aCopy = a;
		a = (a*a - b*b) + c1;
		b = 2 * aCopy * b + c2;

		if(isStop(a, b))
		    return i;
		}
	    return t;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	float c1;
	float c2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
