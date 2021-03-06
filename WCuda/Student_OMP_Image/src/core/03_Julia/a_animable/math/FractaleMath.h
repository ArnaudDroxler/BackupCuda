#pragma once

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractaleMath
    {
    public:
	FractaleMath(uint n);
	virtual ~FractaleMath(void) = 0;

	void colorXY(uchar4* ptrColor, float x, float y, float t);

	bool isStop(float a, float b);

	void setN(uint n);

    private:
	virtual int f(float x, float y, float t) = 0;

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;
    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
