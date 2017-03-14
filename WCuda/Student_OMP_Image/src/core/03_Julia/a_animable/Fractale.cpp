#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"

#include "Fractale.h"
#include "math/FractaleMath.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Fractale::Fractale(uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "04_TP_Julia",domaineMath), variateurAnimation(Interval<float>(nMin, nMax), 1)
    {
    // Tools
    this->ptrFractaleMath = 0;
    this->t = nMin;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Fractale] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Fractale::~Fractale(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Fractale::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [nMin, nMax]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 */
void Fractale::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    FractaleMath* fractaleMath = getFractaleMath(); // ici pour preparer cuda
    fractaleMath->setN(t);
#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    // int s = i * W + j;
	    int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	    workPixel(&ptrTabPixels[s],i,j,domaineMath,fractaleMath);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 */
void Fractale::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    FractaleMath* fractaleMath = getFractaleMath();
    fractaleMath->setN(t);

    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel
	const int TID = OmpTools::getTid();

	int i;
	int j;

	int s = TID; // in [0,...
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    workPixel(&ptrTabPixels[s],i,j,domaineMath,fractaleMath);

	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
void Fractale::workPixel(uchar4* ptrColorIJ,int i, int j,const DomaineMath& domaineMath,FractaleMath* ptrFractaleMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;
    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

   // float t=variateurAnimation.get();

    ptrFractaleMath->colorXY(ptrColorIJ,x, y, t); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

